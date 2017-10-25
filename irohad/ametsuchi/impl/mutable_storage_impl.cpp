/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ametsuchi/impl/mutable_storage_impl.hpp"
#include "crypto/hash.hpp"
#include "model/commands/transfer_asset.hpp"
#include "model/commands/add_asset_quantity.hpp"

#include "ametsuchi/impl/postgres_wsv_command.hpp"
#include "ametsuchi/impl/postgres_wsv_query.hpp"

namespace iroha {
  namespace ametsuchi {
    MutableStorageImpl::MutableStorageImpl(
        hash256_t top_hash,
        std::unique_ptr<cpp_redis::redis_client> index,
        std::unique_ptr<pqxx::lazyconnection> connection,
        std::unique_ptr<pqxx::nontransaction> transaction,
        std::shared_ptr<model::CommandExecutorFactory> command_executors)
        : top_hash_(top_hash),
          index_(std::move(index)),
          connection_(std::move(connection)),
          transaction_(std::move(transaction)),
          wsv_(std::make_unique<PostgresWsvQuery>(*transaction_)),
          executor_(std::make_unique<PostgresWsvCommand>(*transaction_)),
          command_executors_(std::move(command_executors)),
          committed(false) {
      index_->multi();
      transaction_->exec("BEGIN;");
    }

    void MutableStorageImpl::index_block(uint64_t height, const model::Block& block) {
      for (size_t tx_index = 0; tx_index < block.transactions.size(); tx_index++) {
        const auto& tx = block.transactions.at(tx_index);

        // for GetAccountTransactions()
        {
          // to make index creator_account_id -> list of blocks where his txs exist
          index_->rpush(tx.creator_account_id, {std::to_string(height)});

          // to make index creator_account_id:height -> list of tx indexes (where
          // tx is placed in the block)
          index_->rpush(tx.creator_account_id + ":" + std::to_string(height),
                        {std::to_string(tx_index)});
        }

        // for GetAccountAssetTransactions()
        {
          // collect all assets related to user account_id
          std::set<std::pair<std::string, std::string>> users_acct_assets_in_tx;
          std::for_each(tx.commands.begin(),
                        tx.commands.end(),
                        [&users_acct_assets_in_tx](auto command) {
                          if (instanceof<model::TransferAsset>(*command)) {
                            auto transferAsset =
                              (model::TransferAsset *) command.get();
                            users_acct_assets_in_tx.emplace(
                              transferAsset->src_account_id, transferAsset->asset_id);

                            users_acct_assets_in_tx.emplace(
                              transferAsset->dest_account_id, transferAsset->asset_id);
                          } else if (instanceof<model::AddAssetQuantity>(*command)) {
                            auto addAssetQuantity =
                              (model::AddAssetQuantity *) command.get();
                            users_acct_assets_in_tx.emplace(
                              addAssetQuantity->account_id, addAssetQuantity->asset_id);
                          }
                        });

          // to make account_id:height:asset_id -> list of tx indexes (where tx
          // with certain asset is placed in the block )
          for (const auto &acct_asset_id : users_acct_assets_in_tx) {
            // create key to put user's txs with given asset_id
            const auto &account_id = acct_asset_id.first;
            const auto &asset_id = acct_asset_id.second;
            std::string account_assets_key;
            account_assets_key.append(account_id);
            account_assets_key.append(":");
            account_assets_key.append(std::to_string(height));
            account_assets_key.append(":");
            account_assets_key.append(asset_id);
            index_->rpush(account_assets_key, {std::to_string(tx_index)});
          }
        }

        // for pagination of GetAccountTransactions() and
        // GetAccountAssetTransactions(), and for GetTransactions()
        const auto tx_hash_hex = iroha::hash(tx).to_hexstring();
        // to make index tx_hash_hex -> list of blocks where his txs exist
        index_->rpush(tx_hash_hex, {std::to_string(height)});

        // to make index tx_hash_hex:height -> list of tx indexes (where
        // tx is placed in the block)
        index_->rpush(tx_hash_hex + ":" + std::to_string(height),
                      {std::to_string(tx_index)});
      }
    }

    bool MutableStorageImpl::apply(
        const model::Block &block,
        std::function<bool(const model::Block &, WsvQuery &, const hash256_t &)>
            function) {
      auto execute_command = [this](auto command) {
        return command_executors_->getCommandExecutor(command)->execute(
            *command, *wsv_, *executor_);
      };
      auto execute_transaction = [this, execute_command](auto &transaction) {
        return std::all_of(transaction.commands.begin(),
                           transaction.commands.end(),
                           execute_command);
      };

      transaction_->exec("SAVEPOINT savepoint_;");
      auto result = function(block, *wsv_, top_hash_)
          and std::all_of(block.transactions.begin(),
                          block.transactions.end(),
                          execute_transaction);

      if (result) {
        block_store_.insert(std::make_pair(block.height, block));
        index_block(block.height, block);

        top_hash_ = block.hash;
        transaction_->exec("RELEASE SAVEPOINT savepoint_;");
      } else {
        transaction_->exec("ROLLBACK TO SAVEPOINT savepoint_;");
      }
      return result;
    }

    MutableStorageImpl::~MutableStorageImpl() {
      if (not committed) {
        index_->discard();
        transaction_->exec("ROLLBACK;");
      }
    }
  }  // namespace ametsuchi
}  // namespace iroha
