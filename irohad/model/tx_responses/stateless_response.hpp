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

#ifndef IROHA_STATELESS_RESPONSE_HPP
#define IROHA_STATELESS_RESPONSE_HPP

#include "model/transaction_response.hpp"

namespace iroha {
  namespace model {

    /**
     * Transaction response that contains
     */
    struct TransactionStatelessResponse : TransactionResponse {

      /**
       * Is stateless validation passed
       */
      bool passed;
    };
  } // namespace model
} // namespace iroha
#endif //IROHA_STATELESS_RESPONSE_HPP
