#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

TEST_CASE("should update an object's TTL", "[command::peek]") {
	paper::client client ("127.0.0.1", 3145);
	client.wipe();

	SECTION("a key which exists should return ok") {
		client.set("key", "value");
		auto response = client.ttl("key", 5);

		REQUIRE(response->is_ok);
		REQUIRE(response->data == "done");
	}

	SECTION("a key which does not exist should return not ok") {
		auto response = client.ttl("key", 5);

		REQUIRE(!response->is_ok);
		REQUIRE(!response->data.empty());
	}
}
