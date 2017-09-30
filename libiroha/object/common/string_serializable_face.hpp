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

#ifndef IROHA_STRING_SERIALIZABLE_FACE_HPP_
#define IROHA_STRING_SERIALIZABLE_FACE_HPP_

namespace iroha {
  namespace object {
    namespace common {

      /**
       * @class StringSerializableFace
       * @brief Descendants of this interface can be converted into single
       * string.
       */
      class StringSerializableFace {
       public:
        /**
         * @brief Convert object to string.
         * @return string in special format, which is defined by object.
         */
        virtual std::string to_string() = 0;
      };
    }
  }
}
#endif  //  IROHA_STRING_SERIALIZABLE_FACE_HPP_
