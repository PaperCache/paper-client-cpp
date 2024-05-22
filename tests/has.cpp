#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

TEST_CASE("should check if an object exists in the cache", "[command::has]") {
	paper::client client ("paper://127.0.0.1:3145");

	client.auth("auth_token");
	client.wipe();

	SECTION("a key which exists should return true") {
		client.set("key", "value");
		auto response = client.has("key");

		REQUIRE(response->is_ok);
		REQUIRE(response->data);
	}

	SECTION("a key which does not exist should return false") {
		auto response = client.has("key");

		REQUIRE(response->is_ok);
		REQUIRE(!response->data);
	}
}
