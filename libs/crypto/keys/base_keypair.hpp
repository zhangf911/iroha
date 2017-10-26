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

#ifndef IROHA_KEYPAIR_HPP_
#define IROHA_KEYPAIR_HPP_

#include "crypto/keys/base_private_key.hpp"
#include "crypto/keys/base_public_key.hpp"

namespace iroha {
  namespace crypto {

    template <typename Pub, typename Priv>
    class BaseKeypair {
     public:
      BaseKeypair() = default;
      BaseKeypair(const BaseKeypair &) = default;
      BaseKeypair(BaseKeypair &&) noexcept = default;

      BaseKeypair &operator=(const BaseKeypair &) = default;
      BaseKeypair &operator=(BaseKeypair &&) = default;

      static BaseKeypair create(Pub &&pub, Priv &&priv) {
        return BaseKeypair(std::forward<Pub>(pub), std::forward<Priv>(priv));
      }

      const Pub &pubkey() const noexcept { return pub_; }
      Pub pubkey() noexcept { return pub_; }
      const Priv &privkey() const noexcept { return priv_; }

      virtual ~BaseKeypair() {}

     protected:
      Pub pub_;
      Priv priv_;

      BaseKeypair(Pub &&pub, Priv &&priv)
          : pub_(std::move(pub)), priv_(std::move(priv)) {}
    };

  }  // namespace crypto
}  // namespace iroha

#endif  //  IROHA_KEYPAIR_HPP_
