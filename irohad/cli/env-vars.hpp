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

#ifndef IROHA_ENV_VARS_HPP_
#define IROHA_ENV_VARS_HPP_

// peer flags
#define IROHA_PEER_HOST "IROHA_PEER_HOST"
#define IROHA_PEER_PORT "IROHA_PEER_PORT"
#define IROHA_PEER_PUBKEY "IROHA_PEER_PUBKEY"
#define IROHA_PEER_PRIVKEY "IROHA_PEER_PRIVKEY"

// torii flags
#define IROHA_TORII_HOST "IROHA_TORII_HOST"
#define IROHA_TORII_PORT "IROHA_TORII_PORT"

// postgres flags
#define IROHA_PGHOST "IROHA_POSTGRES_HOST"
#define IROHA_PGPORT "IROHA_POSTGRES_PORT"
#define IROHA_PGUSER "IROHA_POSTGRES_USER"
#define IROHA_PGPASSWORD "IROHA_POSTGRES_PASSWORD"
#define IROHA_PGDATABASE "IROHA_POSTGRES_DATABASE"

// redis flags
#define IROHA_RDHOST "IROHA_REDIS_HOST"
#define IROHA_RDPORT "IROHA_REDIS_PORT"

// block storage flags
#define IROHA_BLOCKSPATH "IROHA_BLOCKSPATH"

// other
#define IROHA_OTHER_LOADDELAY "IROHA_OTHER_LOADDELAY"
#define IROHA_OTHER_VOTEDELAY "IROHA_OTHER_VOTEDELAY"
#define IROHA_OTHER_PROPOSALDELAY "IROHA_OTHER_PROPOSALDELAY"
#define IROHA_OTHER_PROPOSALSIZE "IROHA_OTHER_PROPOSALSIZE"

#endif //  IROHA_ENV_VARS_HPP_
