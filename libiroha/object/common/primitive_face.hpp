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

#ifndef IROHA_PRIMITIVE_FACE_HPP_
#define IROHA_PRIMITIVE_FACE_HPP_

namespace iroha {
  namespace object {
    namespace common {

      /**
       * @class PrimitiveFace
       * @brief Abstract interface, which allows descendants validate and create
       * them in unified way.
       * @tparam Type descendant type, which will be created.
       * @tparam Args variadic arguments required to create descendant.
       */
      template <typename Type, typename... Args>
      class PrimitiveFace {
       public:
        /**
         * @brief To create an object valid, input Args should be validated with
         * this function.
         * @param ... arguments to be parsed for validation
         * @return true if object is possible to create with 'from' method,
         * false
         * otherwise.
         */
        virtual bool is_valid(Args...) = 0;

        /**
         * Virtual destructor.
         */
        virtual ~PrimitiveFace() = default;
      };
    }
  }
}

#endif  //  IROHA_PRIMITIVE_FACE_HPP_
