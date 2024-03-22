#include <chrono>
#include <thread>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/client.hpp>

TEST_CASE("should set an object to the cache", "[command::set]") {
	paper::client client ("127.0.0.1", 3145);

	client.auth("auth_token");
	client.wipe();

	SECTION("a TTL of zero should return ok") {
		auto response = client.set("key", "value", 0);

		REQUIRE(response->is_ok);
		REQUIRE(response->data == "done");
	}

	SECTION("a non-zero TTL should return ok") {
		auto response = client.set("key", "value", 1);

		REQUIRE(response->is_ok);
		REQUIRE(response->data == "done");
	}

	SECTION("a non-zero TTL should be correctly set") {
		auto response = client.set("key", "value", 1);

		REQUIRE(response->is_ok);
		REQUIRE(response->data == "done");

		auto got = client.get("key");

		REQUIRE(got->is_ok);
		REQUIRE(got->data == "value");

		std::this_thread::sleep_for(std::chrono::seconds(2));

		auto expired = client.get("key");

		REQUIRE(!expired->is_ok);
		REQUIRE(!expired->data.empty());
	}
}
