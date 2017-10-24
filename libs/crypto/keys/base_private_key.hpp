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

#ifndef IROHA_CRYPTO_KEYS_BASE_PRIVATE_KEY_HPP_
#define IROHA_CRYPTO_KEYS_BASE_PRIVATE_KEY_HPP_

#include "common/types.hpp"
#include "secure/util.hpp"

namespace iroha {
  namespace crypto {

    template <typename T>
    class BasePrivateKey : public BaseBlob<T> {
     public:
      /// use parent constructors
      using BaseBlob<T>::BaseBlob;

      /// default constructible
      BasePrivateKey() = default;

      /// not copy constructible
      BasePrivateKey(BasePrivateKey const &) = delete;

      /// only move constructible
      BasePrivateKey(BasePrivateKey &&other) noexcept {
        this->swap(other);
      }

      /// copy assignment operator
      BasePrivateKey &operator=(BasePrivateKey const &) = delete;

      /// move assignment operator
      BasePrivateKey &operator=(BasePrivateKey &&other) noexcept {
        this->swap(other);
        return *this;
      };

      virtual ~BasePrivateKey() override {
        secure::erase(reinterpret_cast<void *>(this->data()), this->size());
      }
    };
  }
}

#endif  //  IROHA_CRYPTO_KEYS_BASE_PRIVATE_KEY_HPP_
