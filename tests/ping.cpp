#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

TEST_CASE("should ping the cache", "[command::ping]") {
	paper::client client ("paper://127.0.0.1:3145");
	auto response = client.ping();

	REQUIRE(response->is_ok);
	REQUIRE(response->data == "pong");
}
