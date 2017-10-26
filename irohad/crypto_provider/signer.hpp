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

#ifndef IROHA_BASE_SIGNER_HPP_
#define IROHA_BASE_SIGNER_HPP_

#include <memory>
#include <string>

#include <boost/optional.hpp>

// use this algorithm for signer
#include "crypto/ed25519/ed25519.hpp"

namespace iroha {
  namespace crypto {

    class Signer {
     public:
      using message_t = std::string;
      using pubkey_t = ed25519::PublicKey;
      using privkey_t = ed25519::PrivateKey;
      using signature_t = ed25519::Signature;
      using keypair_t = ed25519::Keypair;

      Signer(keypair_t &&kp) : keypair(std::move(kp)) {}
      Signer(const Signer &other) = delete;
      Signer(Signer &&other) noexcept : keypair(std::move(other.keypair)) {}

      static boost::optional<Signer> create(const std::string &pub,
                                            const std::string &priv) {
        auto kp = keypair_t::create(pub, priv);

        if (kp) {
          Signer s(std::move(kp.value()));
          return {};
        } else {
          return boost::none;
        }
      }

      virtual signature_t sign(const message_t &m) const noexcept {
        return ed25519::sign(m, keypair);
      }

     protected:
      const keypair_t keypair;
    };
  }
}

#endif  //  IROHA_BASE_SIGNER_HPP_
