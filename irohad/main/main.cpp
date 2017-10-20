/*
Copyright Soramitsu Co., Ltd. 2016 All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <boost/filesystem.hpp>

#include "main/application.hpp"
#include "main/common.hpp"
#include "main/flags.hpp"
#include "main/raw_block_insertion.hpp"
#include "util/network.hpp"

#include "logger/logger.hpp"

using namespace iroha;

#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)
#define ALLHOST "0.0.0.0"s
#define LOCALHOST "localhost"s

int main(int argc, char *argv[]) {
  auto log = logger::log("MAIN");
  CLI::App main("iroha - simple decentralized ledger");
  main.require_subcommand(1);
  main.add_flag("-v,--version"s,
                [&argv, &main](size_t) {
                  // note (@warchant): do not use logger here, it
                  // looks ugly.
                  std::cout << argv[0] << " version " <<
#ifdef IROHA_VERSION
                      STRINGIFY(IROHA_VERSION)
#else
                      "undefined"
#endif
                            << std::endl;
                  exit(0);
                },
                "Current version"s);

  /// DEFAULTS
  config::Torii torii{};
  torii.host = ALLHOST;
  torii.port = 50051;

  config::Redis redis{};
  redis.host = LOCALHOST;
  redis.port = 6379;

  config::Postgres postgres{};
  postgres.host = LOCALHOST;
  postgres.port = 5432;
  postgres.database = "iroha";

  config::BlockStorage storage{};
  storage.path = "blocks"s;

  config::Cryptography crypto{};

  /// OPTIONS
  auto start = main.add_subcommand("start"s, "Start peer"s);

  auto ledger = main.add_subcommand("ledger"s, "Manage ledger"s);
  ledger->require_subcommand(1);

  auto lcreate = ledger->add_subcommand(
      "create"s, "Create new network with given genesis block"s);
  addCreateLedgerFlags(lcreate, [&argv, &log](std::string genesis) {
    log->info("{} ledger create {} is called", argv[0], genesis);
    BOOST_ASSERT_MSG(false, "not implemented");
  });

  auto lclear = ledger->add_subcommand("clear"s, "Clear peer's ledger"s);
  lclear->set_callback([&log, &argv]() {
    // TODO (@warchant) 20/10/17: implement
    log->info("{} ledger clear is called", argv[0]);
    BOOST_ASSERT_MSG(false, "not implemented");
  });
std::move(config)
  addPeerFlags(start, torii, crypto);
  addPostgresFlags(start, postgres);
  addRedisFlags(start, redis);
  addBlockStorageFlags(start, storage);

  CLI11_PARSE(main, argc, argv);

  try {
    // if something critical can not be parsed, throws exceptions
    // descendants
    // from std::exception
    Application irohad;
    irohad.initStorage(postgres, redis, storage);
    irohad.initProtoFactories();
    irohad.initPeerQuery();
    irohad.initCryptoProvider(crypto);
    irohad.initValidators();
    irohad.initOrderingGate();
    irohad.initSimulator();
    irohad.initBlockLoader();
    irohad.initConsensusGate(torii);
    irohad.initSynchronizer();
    irohad.initPeerCommunicationService();
    irohad.initTransactionCommandService();
    irohad.initQueryService();

    // TODO(@warchant): refactor. Move this to Iroha as a separate
    // module

//    {  // bad :(
//      iroha::main::BlockInserter inserter(irohad.storage);
//
//      // throws if can not open file
//      //      auto content =
//      irohad.config().blockchainOptions().genesis_block;
//      auto block = inserter.parseBlock(content);
//      log->info("Block parsed");
//
//      if (block.has_value()) {
//        inserter.applyToLedger({block.value()});
//        log->info("Genesis block inserted, number of transactions: {} ",
//                  block.value().transactions.size());
//      } else {
//        throw std::logic_error("Block can not be parsed from JSON");
//      }
//    }

    // runs iroha
    log->info("iroha initialized");
    irohad.run(torii);

  } catch (const std::exception &e) {
    log->error("FATAL: {}", e.what());
  }

  return 0;
}
