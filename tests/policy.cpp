#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

paper::policy get_current_policy(paper::client&);

TEST_CASE("should set the cache's policy", "[command::policy]") {
	const paper::policy INITIAL_POLICY = paper::policy::LFU;
	const paper::policy UPDATED_POLICY = paper::policy::LRU;

	paper::client client ("127.0.0.1", 3145);
	client.wipe();

	auto initial = client.policy(INITIAL_POLICY);

	REQUIRE(initial->is_ok);
	REQUIRE(initial->data == "done");
	REQUIRE(get_current_policy(client) == INITIAL_POLICY);

	auto updated = client.policy(UPDATED_POLICY);

	REQUIRE(updated->is_ok);
	REQUIRE(updated->data == "done");
	REQUIRE(get_current_policy(client) == UPDATED_POLICY);
}

paper::policy get_current_policy(paper::client& client) {
	auto response = client.stats();
	return response->stats.policy;
}
