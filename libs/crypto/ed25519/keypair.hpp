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

#ifndef IROHA_CRYPTO_ED25519_KEYPAIR_HPP_
#define IROHA_CRYPTO_ED25519_KEYPAIR_HPP_

#include "common/helper.hpp"
#include "crypto/keys/base_keypair.hpp"
#include "crypto/keys/base_private_key.hpp"
#include "crypto/keys/base_public_key.hpp"

#include <boost/optional.hpp>

#define IROHA_ED25519_PRIVKEY_SIZE 64
#define IROHA_ED25519_PUBKEY_SIZE 32
#define IROHA_ED25519_SIGNATURE_SIZE 64

namespace iroha {
  namespace crypto {
    namespace ed25519 {

      class PrivateKey
          : public BasePrivateKey<std::array<uint8_t,
                                             IROHA_ED25519_PRIVKEY_SIZE> > {};

      class PublicKey
          : public BasePublicKey<std::array<uint8_t,
                                            IROHA_ED25519_PUBKEY_SIZE> > {};

      class Signature
          : public BaseBlob<std::array<uint8_t,
                                       IROHA_ED25519_SIGNATURE_SIZE> > {};

      class Keypair : public BaseKeypair<PublicKey, PrivateKey> {
       public:
        Keypair(PublicKey &&pub, PrivateKey &&priv)
            : BaseKeypair<PublicKey, PrivateKey>(std::move(pub),
                                                 std::move(priv)) {}

        static boost::optional<Keypair> create(const std::string &pub,
                                               const std::string &priv) {
          using helper::make_array;
          PublicKey pub_;
          PrivateKey priv_;

          if (!make_array(reinterpret_cast<PublicKey::Type *>(&pub_), pub)) {
            return boost::none;
          }

          if (!make_array(reinterpret_cast<PrivateKey::Type *>(&priv_), priv)) {
            return boost::none;
          }

          return Keypair(std::move(pub_), std::move(priv_));
        }
      };
    }
  }
}

#endif  //  IROHA_CRYPTO_ED25519_KEYPAIR_HPP_
