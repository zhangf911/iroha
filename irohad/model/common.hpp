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

#ifndef IROHA_COMMON_HPP
#define IROHA_COMMON_HPP

#include <memory>
#include "common/types.hpp"
#include "crypto/crypto.hpp"
#include "crypto/hash.hpp"
#include "model/signature.hpp"
#include "model/transaction.hpp"
#include "model/block.hpp"

namespace iroha {
  namespace model {
    // Optional over shared pointer
    template <typename T>
    using optional_ptr = nonstd::optional<std::shared_ptr<T>>;

    template <typename T, typename... Args>
    optional_ptr<T> make_optional_ptr(Args &&... args) {
      return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    void sign(T& t, nonstd::optional<iroha::keypair_t> p) {
      if (!p.has_value()) return;
  
      const auto &pair = p.value();
      auto hash_ = hash(t);
      auto sign = iroha::sign(hash_.data(), hash_.size(), pair.pubkey, pair.privkey);
  
      model::Signature signature{};
      signature.signature = sign;
      signature.pubkey = pair.pubkey;
  
      add_signature(t, signature);
    }
  
    inline void add_signature(model::Transaction &tx, model::Signature &s) {
      tx.signatures.push_back(s);
    }
  
    inline void add_signature(model::Query &query, model::Signature &s) {
      query.signature.signature = s.signature;
    }
  
    inline void add_signature(model::Block &block, model::Signature &s) {
      block.sigs.push_back(s);
    }
  }  // namespace model
}  // namespace iroha

#endif  // IROHA_COMMON_HPP
