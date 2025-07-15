/*
 * Copyright (c) Kia Shakiba
 *
 * This source code is licensed under the GNU AGPLv3 license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

TEST_CASE("should get the cache's status", "[command::status]") {
	paper::client client ("paper://127.0.0.1:3145");

	client.auth("auth_token");
	client.wipe();

	auto response = client.status();

	REQUIRE(response->is_ok);
}
