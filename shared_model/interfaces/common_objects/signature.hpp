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

#ifndef IROHA_SHARED_MODEL_SIGNATURE_HPP
#define IROHA_SHARED_MODEL_SIGNATURE_HPP

#include "interfaces/common_objects/hash.hpp"
#include "interfaces/primitive.hpp"
#include "model/signature.hpp"
#include "utils/string_builder.hpp"

namespace shared_model {
  namespace interface {

    /**
     * Class represents signature of high-level domain objects.
     */
    class Signature : public Primitive<Signature, iroha::model::Signature> {
     public:
      /**
       * Type of hashes
       */
      using HashType = Hash;

      /**
       * @return public key of signatory
       */
      virtual const HashType &publicKey() const = 0;

      /**
       * @return signed hash of message
       */
      virtual const HashType &signedHash() const = 0;

      bool operator==(const Signature &rhs) const override {
        return this->publicKey() == rhs.publicKey()
            and this->signedHash() == rhs.signedHash();
      }

      OldModelType *makeOldModel() const override {
        iroha::model::Signature *oldStyleSignature =
            new iroha::model::Signature();
        oldStyleSignature->signature =
            iroha::model::Signature::SignatureType::from_string(
                signedHash().toString());
        oldStyleSignature->pubkey =
            iroha::model::Signature::KeyType::from_string(
                publicKey().toString());
        return oldStyleSignature;
      }

      std::string toString() const override {
        return detail::PrettyStringBuilder()
            .init("Signature")
            .append("publicKey", publicKey().hex())
            .append("signedHash", signedHash().hex())
            .finalize();
      }
    };
  }  // namespace interface
}  // namespace shared_model
#endif  // IROHA_SHARED_MODEL_SIGNATURE_HPP