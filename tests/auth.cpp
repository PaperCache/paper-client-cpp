/*
 * Copyright (c) Kia Shakiba
 *
 * This source code is licensed under the GNU AGPLv3 license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

TEST_CASE("should not authorize with incorrect token", "[command::auth]") {
	paper::client client ("paper://127.0.0.1:3145");

	REQUIRE(!client.set("key", "value")->is_ok);

	auto response = client.auth("incorrect_auth_token");

	REQUIRE(!response->is_ok);
	REQUIRE(!client.set("key", "value")->is_ok);
}

TEST_CASE("should authorize with correct token", "[command::auth]") {
	paper::client client ("paper://127.0.0.1:3145");

	REQUIRE(!client.set("key", "value")->is_ok);

	auto response = client.auth("auth_token");

	REQUIRE(response->is_ok);
	REQUIRE(client.set("key", "value")->is_ok);
}
