#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

TEST_CASE("should peek an object from the cache", "[command::peek]") {
	paper::client client ("127.0.0.1", 3145);
	client.wipe();

	SECTION("a key which exists should return ok") {
		client.set("key", "value");
		auto response = client.peek("key");

		REQUIRE(response->is_ok);
		REQUIRE(response->data == "value");
	}

	SECTION("a key which does not exist should return not ok") {
		auto response = client.peek("key");

		REQUIRE(!response->is_ok);
		REQUIRE(!response->data.empty());
	}
}
