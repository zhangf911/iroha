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

#ifndef IROHA_COMMON_HELPERS_HPP_
#define IROHA_COMMON_HELPERS_HPP_

#include <array>
#include <boost/optional.hpp>

namespace iroha {
  namespace helper {

    /**
     * Helper to create std::array from arbitrary STL container.
     * @tparam T element type of std::array
     * @tparam size_ size of returned std::array
     * @tparam Container STL container which has begin, size, end methods
     * @param a instance of STL container
     * @return boost::none if size_ != a.size(), std::array otherwise
     */
    template <typename T, size_t size_, typename Container>
    boost::optional<std::array<T, size_>> make_array(Container &&a) {
      if (a.size() != size_) {
        return boost::none;
      }

      std::array<T, size_> ret;
      std::copy(a.begin(), a.end(), ret.begin());
      return ret;
    }

    /**
     * Helper to fill std::array with data, given in form of arbitrary STL
     * container.
     *
     * Can be used to avoid double copying (container -> temp std::array ->
     * target std::array)
     *
     * @tparam T element type of std::array
     * @tparam size_ size of std::array
     * @tparam Container STL container which has begin, size, end methods
     * @param ret non-null ptr to array, which will be filled with Container's
     * data
     * @param a instance of STL container
     * @return true, if Container has the same length as given size_
     */
    template <typename T, size_t size_, typename Container>
    bool make_array(std::array<T, size_> *ret, Container &&a) {
      BOOST_ASSERT_MSG(ret != nullptr, "ptr argument is nullptr: " __FILE__);

      if (a.size() != size_) {
        return false;
      }

      std::copy(a.begin(), a.end(), ret->begin());
      return true;
    }
  }
}

#endif  //  IROHA_COMMON_HELPERS_HPP_
