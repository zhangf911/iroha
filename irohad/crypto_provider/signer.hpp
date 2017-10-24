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

#include <string>

namespace iroha {
  namespace crypto {

    /**
     * CRTP
     * @tparam ConcreteSigner
     */
    template <typename ConcreteSigner>
    class Signer {
     public:
      using message_t = std::string;

      auto sign(const message_t &m) const noexcept {
        return static_cast<ConcreteSigner *>(this)->sign(m);
      }
    };
  }
}

#endif  //  IROHA_BASE_SIGNER_HPP_
