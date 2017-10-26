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

#include "crypto/ed25519/ed25519.hpp"
#include "secure/prng.hpp"

extern "C" {
#include "crypto/ed25519/c_ed25519/ed25519.h"
}

namespace iroha {
  namespace crypto {
    namespace ed25519 {

      static secure::prng<uint8_t> prng;

      Signature sign(const message_t &m, const Keypair &kp) {
        Signature s{};
        ed25519_sign(s.data(),
                     reinterpret_cast<const uint8_t *>(m.data()),
                     m.size(),
                     kp.pubkey().data(),
                     kp.privkey().data());
        return s;
      }

      bool verify(const message_t &m, const PublicKey &p, const Signature &s) {
        return 1 == ed25519_verify(s.data(),
                                   reinterpret_cast<const uint8_t *>(m.data()),
                                   m.size(),
                                   p.data());
      }

      std::shared_ptr<Signature> sign(const message_t &,
                                      const std::unique_ptr<Keypair> kp){
        std::shared_ptr<Signature> s = std::make_shared<Signature>();

        ed25519_sign(s->data(),
                     reinterpret_cast<const uint8_t *>(m.data()),
                     m.size(),
                     kp.pubkey().data(),
                     kp.privkey().data());
        return s;
      }

      bool verify(const message_t &,
                  const std::shared_ptr<PublicKey>,
                  const std::shared_ptr<Signature>);

      seed_t generate_seed() {
        seed_t seed;
        auto v = prng.get(32);
        std::copy(v.begin(), v.end(), seed.begin());
        return seed;
      }

      seed_t generate_seed(const std::string &passphrase) {
        // TODO: implement. Do we need this at all?
        BOOST_ASSERT_MSG(false, "generate_seed(passphrase) is not implemented");
      }

      Keypair generate_keypair() {
        seed_t seed = generate_seed();
        Keypair kp = std::move(generate_keypair(seed));
        return kp;
      }

      Keypair generate_keypair(const seed_t &seed) {
        PublicKey pub;
        PrivateKey priv;

        ed25519_create_keypair(pub.data(), priv.data(), seed.data());

        return Keypair(std::move(pub), std::move(priv));
      }
    }
  }
}
