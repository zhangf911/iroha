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

#include <gtest/gtest.h>
#include "crypto_provider/ed25519/ed25519signer.hpp"
#include "crypto_provider/ed25519/ed25519verifier.hpp"

using namespace iroha::crypto;

TEST(Ed25519, SignThenVerify) {
  ed25519::seed_t seed{};  // filled with zeros
  auto keypair = ed25519::generate_keypair(seed);

  Signer<ed25519::Ed25519Signer> signer(std::move(keypair));
  Verifier<ed25519::Ed25519Verifier> verifier;

  std::string message = R"(
Let me tell you all a story about a mouse named Lorry
Yeah, Lorry was a mouse in a big brown house
She called herself the hoe, with the money money flow
But fuck that little mouse 'cause I'm an albatraoz
)";

  auto signature = signer.sign(message);

  ASSERT_TRUE(verifier.verify(signature, message, keypair.pubkey()))
      << "sign then verify should be true";
}
