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

#ifndef IROHA_PB_QUERY_RESPONSE_FACTORY_HPP
#define IROHA_PB_QUERY_RESPONSE_FACTORY_HPP

#include <responses.pb.h>
#include <boost/optional.hpp>
#include <model/account_asset.hpp>
#include <model/queries/responses/account_assets_response.hpp>
#include <model/queries/responses/account_response.hpp>
#include "model/queries/responses/asset_response.hpp"
#include "model/queries/responses/error_response.hpp"
#include "model/queries/responses/roles_response.hpp"
#include "model/queries/responses/signatories_response.hpp"
#include "model/queries/responses/transactions_response.hpp"

namespace iroha {
  namespace model {
    namespace converters {
      /**
       * Converting business objects to protobuf and vice versa
       */
      class PbQueryResponseFactory {
        template <typename T>
        using opt<T> = boost::optional<T>;
        boost::none_t none;

       public:
        /// contract for the interface of serializers
        template <typename T, typename U>
        T serialize(const U &) const;

        /// contract for the interface of deserializers
        template <typename T, typename U>
        opt<T> deserialize(const U &) const;

        template <>
        protocol::QueryResponse serialize(const model::QueryResponse &) const;

        template <>
        opt<model::QueryResponse> deserialize(
            const protocol::QueryResponse &) const;

        /// serialize model::Account
        template <>
        protocol::Account serialize(const model::Account &) const;

        /// deserialize model::Account
        template <>
        opt<model::Account> deserialize(const protocol::Account &) const;

        /// serialize model::AccountResponse
        template <>
        protocol::AccountResponse serialize(
            const model::AccountResponse &) const;

        /// deserialize model::AccountResponse
        template <>
        opt<model::AccountResponse> deserialize(
            const protocol::AccountResponse &) const;

        /// serialize model::AccountAsset
        template <>
        protocol::AccountAsset serialize(const model::AccountAsset &) const;

        /// deserialize model::AccountAsset
        template <>
        opt<model::AccountAsset> deserialize(
            const protocol::AccountAsset &) const;

        /// serialize model::AccountAsset
        template <>
        protocol::AccountAssetResponse serialize(
            const model::AccountAssetResponse &) const;

        /// deserialize model::AccountAsset
        template <>
        opt<model::AccountAssetResponse> deserialize(
            const protocol::AccountAssetResponse &) const;

        /// serialize model::SignatoriesResponse
        template <>
        protocol::SignatoriesResponse serialize(
            const model::SignatoriesResponse &) const;

        /// deserialize model::SignatoriesResponse
        template <>
        opt<model::SignatoriesResponse> deserialize(
            const protocol::SignatoriesResponse &) const;

        /// serialize model::TransactionsResponse
        template <>
        protocol::TransactionsResponse serialize(
            const model::TransactionsResponse &) const;

        /// deserialize model::TransactionsResponse
        //        // TODO(@warchant): not implemented, implement
        //        template <>
        //        opt<model::TransactionsResponse> deserialize(
        //            const protocol::TransactionsResponse &) const;

        /// serialize model::AssetResponse
        template <>
        protocol::AssetResponse serialize(const model::AssetResponse &) const;

        /// deserialize model::AssetResponse
        template <>
        opt<model::AssetResponse> deserialize(
            const protocol::AssetResponse &) const;

        /// serialize model::RolesResponse
        template <>
        protocol::RolesResponse serialize(const model::RolesResponse &) const;

        /// deserialize model::RolesResponse
        template <>
        opt<model::RolesResponse> deserialize(
            const protocol::RolesResponse &) const;

        /// serialize model::RolePermissionsResponse
        template <>
        protocol::RolePermissionsResponse serialize(
            const model::RolePermissionsResponse &) const;

        /// deserialize model::RolePermissionsResponse
        template <>
        opt<model::RolePermissionsResponse> deserialize(
            const protocol::RolePermissionsResponse &) const;

        template <>
        protocol::ErrorResponse serialize(
            const model::ErrorResponse &errorResponse) const;
      };
    }
  }
}

#endif  // IROHA_PB_QUERY_RESPONSE_FACTORY_HPP
