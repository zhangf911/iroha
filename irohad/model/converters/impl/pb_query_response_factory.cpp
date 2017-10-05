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

#include "model/converters/pb_query_response_factory.hpp"
#include <boost/assert.hpp>
#include "model/converters/pb_common_face.hpp"
#include "model/converters/pb_transaction_factory.hpp"

namespace iroha {
  namespace model {
    namespace converters {

      template <>
      protocol::ErrorResponse PbQueryResponseFactory::serialize(
          const model::ErrorResponse &m) const {
        protocol::ErrorResponse p;
        switch (m.reason) {
          case ErrorResponse::NO_ASSET:
            p.set_reason(protocol::ErrorResponse::NO_ASSET);
            break;
          case ErrorResponse::STATELESS_INVALID:
            p.set_reason(protocol::ErrorResponse::STATELESS_INVALID);
            break;
          case ErrorResponse::STATEFUL_INVALID:
            p.set_reason(protocol::ErrorResponse::STATEFUL_INVALID);
            break;
          case ErrorResponse::NO_ACCOUNT:
            p.set_reason(protocol::ErrorResponse::NO_ACCOUNT);
            break;
          case ErrorResponse::NO_ACCOUNT_ASSETS:
            p.set_reason(protocol::ErrorResponse::NO_ACCOUNT_ASSETS);
            break;
          case ErrorResponse::NO_SIGNATORIES:
            p.set_reason(protocol::ErrorResponse::NO_SIGNATORIES);
            break;
          case ErrorResponse::NOT_SUPPORTED:
            p.set_reason(protocol::ErrorResponse::NOT_SUPPORTED);
            break;
          case ErrorResponse::NO_ROLES:
            p.set_reason(protocol::ErrorResponse::NO_ROLES);
            break;
          default:
            BOOST_ASSERT_MSG(false, "not implemented");
            break;
        }
        return p;
      }

      template <>
      protocol::QueryResponse PbQueryResponseFactory::serialize(
          const model::QueryResponse &m) const {
        protocol::QueryResponse p;
      }
      template <>
      opt<model::QueryResponse> PbQueryResponseFactory::deserialize(
          const protocol::QueryResponse &) const {
        return none;
      }

      template <>
      protocol::Account PbQueryResponseFactory::serialize(
          const model::Account &m) const {
        protocol::Account p{};
        p.set_quorum(m.quorum);
        p.set_account_id(m.account_id);
        p.set_domain_name(m.domain_name);

        auto permissions = p.mutable_permissions();
        permissions->set_set_quorum(m.permissions.set_quorum);
        permissions->set_set_permissions(m.permissions.set_permissions);
        permissions->set_remove_signatory(m.permissions.remove_signatory);
        permissions->set_read_all_accounts(m.permissions.read_all_accounts);
        permissions->set_issue_assets(m.permissions.issue_assets);
        permissions->set_create_domains(m.permissions.create_domains);
        permissions->set_create_accounts(m.permissions.create_accounts);
        permissions->set_create_assets(m.permissions.create_assets);
        permissions->set_can_transfer(m.permissions.can_transfer);
        permissions->set_add_signatory(m.permissions.add_signatory);

        return p;
      }

      template <>
      opt<model::Account> PbQueryResponseFactory::deserialize(
          const protocol::Account &p) const {
        model::Account m{};
        m.account_id = p.account_id();
        m.quorum = p.quorum();
        m.domain_name = p.domain_name();

        m.permissions.add_signatory = p.permissions().add_signatory();
        m.permissions.can_transfer = p.permissions().can_transfer();
        m.permissions.create_assets = p.permissions().create_assets();
        m.permissions.create_accounts = p.permissions().create_accounts();
        m.permissions.create_domains = p.permissions().create_domains();
        m.permissions.issue_assets = p.permissions().issue_assets();
        m.permissions.read_all_accounts = p.permissions().read_all_accounts();
        m.permissions.remove_signatory = p.permissions().remove_signatory();
        m.permissions.set_permissions = p.permissions().set_permissions();
        m.permissions.set_quorum = p.permissions().set_quorum();

        return m;
      }

      template <>
      protocol::AccountResponse PbQueryResponseFactory::serialize(
          const model::AccountResponse &m) const {
        protocol::AccountResponse p{};
        p.mutable_account()->CopyFrom(serialize(m.account));
        return p;
      }

      template <>
      opt<model::AccountResponse> PbQueryResponseFactory::deserialize(
          const protocol::AccountResponse &p) const {
        model::AccountResponse m{};

        auto d = deserialize(p.account());
        if (d) {
          m.account = d.value();
          // TODO(@warchant): should we set m.query_hash?

          return m;
        } else {
          return none;
        }
      }

      template <>
      protocol::AccountAsset PbQueryResponseFactory::serialize(
          const AccountAsset &m) const {
        protocol::AccountAsset p{};
        p.set_account_id(m.account_id);
        p.set_asset_id(m.asset_id);
        p.mutable_balance()->CopyFrom(serialize(m.balance));
        return p;
      }

      template <>
      opt<model::AccountAsset> PbQueryResponseFactory::deserialize(
          const protocol::AccountAsset &p) const {
        model::AccountAsset m{};
        m.account_id = p.account_id();
        m.balance = deserialize(p.balance());
        m.asset_id = p.asset_id();
        return m;
      }

      template <>
      protocol::AccountAssetResponse PbQueryResponseFactory::serialize(
          const model::AccountAssetResponse &m) const {
        protocol::AccountAssetResponse p{};
        auto a = p.mutable_account_asset();
        a->set_asset_id(m.acct_asset.asset_id);
        a->set_account_id(m.acct_asset.account_id);
        a->mutable_balance()->CopyFrom(serialize(m.acct_asset.balance));
        return p;
      }

      template <>
      opt<model::AccountAssetResponse> PbQueryResponseFactory::deserialize(
          const protocol::AccountAssetResponse &p) const {
        model::AccountAssetResponse m{};
        m.acct_asset.account_id = p.account_asset().account_id();
        m.acct_asset.asset_id = p.account_asset().asset_id();
        auto d = deserialize(p.account_asset().balance());
        if (d) {
          m.acct_asset.balance = d.value();
          // TODO(@warchant): query hash is empty here

          return m;
        } else {
          return none;
        }
      }

      template <>
      protocol::SignatoriesResponse PbQueryResponseFactory::serialize(
          const model::SignatoriesResponse &m) const {
        protocol::SignatoriesResponse p{};

        for (const auto &key : m.keys) {
          p.add_keys(key.data(), key.size());
        }

        return p;
      }

      template <>
      opt<model::SignatoriesResponse> PbQueryResponseFactory::deserialize(
          const protocol::SignatoriesResponse &p) const {
        model::SignatoriesResponse res{};

        res.keys.resize(static_cast<unsigned long>(p.keys_size()));
        for (const auto &key : p.keys()) {
          // TODO(@warchant): there should be validation
          pubkey_t pubkey;
          std::copy(key.begin(), key.end(), pubkey.begin());
          res.keys.push_back(pubkey);
        }

        return res;
      }

      template <>
      protocol::TransactionsResponse PbQueryResponseFactory::serialize(
          const model::TransactionsResponse &m) const {
        PbTransactionFactory p{};

        // converting observable to the vector using reduce
        return m.transactions
            .reduce(protocol::TransactionsResponse(),
                    [&p](auto &&response, const auto &tx) {
                      response.add_transactions()->CopyFrom(p.serialize(tx));
                      return response;
                    },
                    [](auto &&response) { return response; })
            .as_blocking()  // we need to wait when on_complete happens
            .first();
      }

      template <>
      protocol::AssetResponse PbQueryResponseFactory::serialize(
          const model::AssetResponse &m) const {
        protocol::AssetResponse p{};
        auto asset = p.mutable_asset();
        asset->set_asset_id(m.asset.asset_id);
        asset->set_domain_id(m.asset.domain_id);
        asset->set_precision(m.asset.precision);
        return p;
      }

      template <>
      opt<model::AssetResponse> PbQueryResponseFactory::deserialize(
          const protocol::AssetResponse &p) const {
        model::AssetResponse m{};
        auto asset = p.asset();

        // TODO(@warchant): run-time validator should be here
        BOOST_ASSERT_MSG(asset.precision() >= 0 && asset.precision() < 256,
                         "Precision is out of bounds");

        m.asset = Asset(asset.asset_id(),
                        asset.domain_id(),
                        static_cast<uint8_t>(asset.precision()));
        return m;
      }

      template <>
      protocol::RolesResponse PbQueryResponseFactory::serialize(
          const model::RolesResponse &m) const {
        protocol::RolesResponse p{};
        for (const auto &role : m.roles) {
          p.add_roles(role);
        }
        return p;
      }

      template <>
      opt<model::RolesResponse> PbQueryResponseFactory::deserialize(
          const protocol::RolesResponse &p) const {
        model::RolesResponse m{};

        if (p.roles_size() == 0) return none;

        std::copy(p.roles().begin(), p.roles().end(), m.roles.begin());
        return m;
      }

      template <>
      protocol::RolePermissionsResponse PbQueryResponseFactory::serialize(
          const model::RolePermissionsResponse &m) const {
        protocol::RolePermissionsResponse p{};
        for (const auto &perm : m.role_permissions) {
          p.add_permissions(perm);
        }
        return p;
      }

      template <>
      opt<model::RolePermissionsResponse> PbQueryResponseFactory::deserialize(
          const protocol::RolePermissionsResponse &p) const {
        model::RolePermissionsResponse m{};
        std::copy(p.permissions().begin(),
                  p.permissions().end(),
                  m.role_permissions.begin());
        return m;
      }
    }  // namespace converters
  }    // namespace model
}  // namespace iroha
