/*
 * Copyright (c) Kia Shakiba
 *
 * This source code is licensed under the GNU AGPLv3 license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

uint64_t get_current_size(paper::client&);

TEST_CASE("should resize the cache", "[command::resize]") {
	const uint64_t INITIAL_SIZE = 10485760;
	const uint64_t UPDATED_SIZE = 20971520;

	paper::client client ("paper://127.0.0.1:3145");

	client.auth("auth_token");
	client.wipe();

	auto initial = client.resize(INITIAL_SIZE);

	REQUIRE(initial->is_ok);
	REQUIRE(get_current_size(client) == INITIAL_SIZE);

	auto updated = client.resize(UPDATED_SIZE);

	REQUIRE(updated->is_ok);
	REQUIRE(get_current_size(client) == UPDATED_SIZE);
}

uint64_t get_current_size(paper::client& client) {
	auto response = client.status();
	return response->status.max_size;
}
