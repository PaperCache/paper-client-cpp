/*
 * Copyright (c) Kia Shakiba
 *
 * This source code is licensed under the GNU AGPLv3 license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

std::string get_current_policy(paper::client&);

TEST_CASE("should set the cache's policy", "[command::policy]") {
	const std::string INITIAL_POLICY = std::string("lfu");
	const std::string UPDATED_POLICY = std::string("lru");

	paper::client client ("paper://127.0.0.1:3145");

	client.auth("auth_token");
	client.wipe();

	auto initial = client.policy(INITIAL_POLICY);

	REQUIRE(initial->is_ok);
	REQUIRE(get_current_policy(client) == INITIAL_POLICY);

	auto updated = client.policy(UPDATED_POLICY);

	REQUIRE(updated->is_ok);
	REQUIRE(get_current_policy(client) == UPDATED_POLICY);
}

std::string get_current_policy(paper::client& client) {
	auto response = client.stats();
	return response->stats.policy;
}
