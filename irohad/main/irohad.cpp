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

#include <gflags/gflags.h>
#include <grpc++/grpc++.h>
#include <fstream>
#include <fstream>
#include <sstream>
#include <thread>
#include "main/application.hpp"
#include "main/iroha_conf_loader.hpp"
#include "main/raw_block_insertion.hpp"

#include "logger/logger.hpp"

auto log_ = logger::log("MAIN");

bool validate_config(const char *flag_name, std::string const &path) {
  return not path.empty();
}

bool validate_genesis_path(const char *flag_name, std::string const &path) {
  return not path.empty();
}

/**
 * Parse keypair file.
 * @param path expects to receive reachable {name}.keypair file, first line
 * should contain hexencoded pubkey, second line should contain hexencoded
 * privatekey.
 * @return
 */
// TODO: (@warchant) refactor
iroha::keypair_t parse_keypair(std::string path) {
  std::ifstream keyfile(path);
  if (not keyfile) {
    log_->warn("there is no keypair file at {}", path);
    exit(1);  // fixme(@warchant)
  } else {
    std::string pub, priv;
    keyfile >> pub >> priv;

    iroha::keypair_t kp;
    try {
      // now size values are hardcoded
      kp.pubkey = *iroha::hexstringToArray<iroha::pubkey_t::size()>(pub);
      kp.privkey = *iroha::hexstringToArray<iroha::privkey_t::size()>(priv);
    } catch (const std::exception &e) {
      log_->warn("keypair can not be parsed");
      exit(1);  // fixme(@warchant)
    }

    return kp;
  }
}

DEFINE_string(config, "", "Specify iroha provisioning path.");
DEFINE_validator(config, &validate_config);

DEFINE_string(genesis_block, "genesis.json", "Specify file with initial block");
DEFINE_validator(genesis_block, &validate_genesis_path);

DEFINE_string(keypair,
              "default.keypair",
              "Specify peer's ed25519 keypair. First line contains hexencoded "
              "pubkey, second line hexencoded private key.");

DEFINE_uint64(peer_number, 0, "Specify peer number");

int main(int argc, char *argv[]) {
  log_->info("start");
  namespace mbr = config_members;

  gflags::ParseCommandLineFlags(&argc, &argv, true);
  gflags::ShutDownCommandLineFlags();

  auto config = parse_iroha_config(FLAGS_config);
  log_->info("config initialized");
  Irohad irohad(config[mbr::BlockStorePath].GetString(),
                config[mbr::RedisHost].GetString(),
                config[mbr::RedisPort].GetUint(),
                config[mbr::PgOpt].GetString(),
                config[mbr::ToriiPort].GetUint(),
                FLAGS_peer_number);

  // TODO(@warchant): refactor
  irohad.setKeypair(parse_keypair(FLAGS_keypair));

  if (not irohad.storage) {
    log_->error("Failed to initialize storage");
    return EXIT_FAILURE;
  }

  iroha::main::BlockInserter inserter(irohad.storage);
  auto file = inserter.loadFile(FLAGS_genesis_block);
  auto block = inserter.parseBlock(file.value());
  log_->info("Block is parsed");

  if (block.has_value()) {
    inserter.applyToLedger({block.value()});
    log_->info("Genesis block inserted, number of transactions: {}",
               block.value().transactions.size());
  }
  // init pipeline components
  irohad.init();

  // runs iroha
  log_->info("Running iroha");
  irohad.run();

  return 0;
}
