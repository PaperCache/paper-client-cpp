#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

TEST_CASE("should get the cache's stats", "[command::stats]") {
	paper::client client ("127.0.0.1", 3145);

	client.auth("auth_token");
	client.wipe();

	auto response = client.stats();

	REQUIRE(response->is_ok);
}
