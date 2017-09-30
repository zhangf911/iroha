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

#ifndef IROHA_ACCOUNT_HPP_
#define IROHA_ACCOUNT_HPP_

#include "primitive_face.hpp"
#include "string_serializable_face.hpp"

namespace iroha {
  namespace object {
    namespace common {

      /**
       * @class Account
       * @brief represents the username
       * @inherit PrimitiveFace<Account, std::string> defines the following
       * logic: object Account can be created from single std::string
       * @inherit StringSerializableFace object Account can be serialized to
       * string. Format 'name'
       */
      class Account : public PrimitiveFace<Account, std::string>,
                      public StringSerializableFace {
       public:


       private:
        Account(std::string arg) : name_(arg) {}
        std::string name_;
      };
    }
  }
}

#endif  //  IROHA_ACCOUNT_HPP_
