#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

TEST_CASE("should get an object's size", "[command::size]") {
	paper::client client ("127.0.0.1", 3145);
	client.wipe();

	SECTION("a key which exists should return its size") {
		client.set("key", "value");
		auto response = client.size("key");

		REQUIRE(response->is_ok);
		REQUIRE(response->data == 5);
	}

	SECTION("a key which does not exist should return not ok") {
		auto response = client.size("key");

		REQUIRE(!response->is_ok);
		REQUIRE(!response->err_data.empty());
	}
}
