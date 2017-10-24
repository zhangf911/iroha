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

#ifndef IROHA_CRYPTO_KEYS_BASE_PUBLIC_KEY_HPP_
#define IROHA_CRYPTO_KEYS_BASE_PUBLIC_KEY_HPP_

#include "common/types.hpp"

namespace iroha {
  namespace crypto {

    template <typename T>
    class BasePublicKey : public BaseBlob<T> {
     public:
      /// use parent constructors
      using BaseBlob<T>::BaseBlob;

      /// default constructible
      BasePublicKey() = default;

      /// copy constructible
      BasePublicKey(BasePublicKey const &) = default;

      /// move constructible
      BasePublicKey(BasePublicKey &&) noexcept = default;

      /// copy assignment operator
      BasePublicKey &operator=(BasePublicKey const &) = default;

      /// move assignment operator
      BasePublicKey &operator=(BasePublicKey &&) noexcept = default;

      virtual ~BasePublicKey() override = default;
    };
  }
}

#endif  //  IROHA_CRYPTO_KEYS_BASE_PUBLIC_KEY_HPP_
