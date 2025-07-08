/*
 * Copyright (c) Kia Shakiba
 *
 * This source code is licensed under the GNU AGPLv3 license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

TEST_CASE("should get the cache's version", "[command::version]") {
	paper::client client ("paper://127.0.0.1:3145");
	auto response = client.version();

	REQUIRE(response->is_ok);
	REQUIRE(!response->data.empty());
}
