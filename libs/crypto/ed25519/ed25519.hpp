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

#ifndef IROHA_CRYPTO_ED25519_INTERFACE_HPP_
#define IROHA_CRYPTO_ED25519_INTERFACE_HPP_

#include <memory>
#include <string>
#include "crypto/ed25519/keypair.hpp"

namespace iroha {
  namespace crypto {
    namespace ed25519 {

      using message_t = std::string;
      using seed_t = std::array<uint8_t, 32>;

      Signature sign(const message_t &, const Keypair &kp);

      bool verify(const message_t &, const PublicKey &, const Signature &);

      seed_t generate_seed();
      seed_t generate_seed(const std::string &passphrase);

      Keypair generate_keypair();
      Keypair generate_keypair(const seed_t &);
    }
  }
}

#endif  //  IROHA_CRYPTO_ED25519_INTERFACE_HPP_
