#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/pool.hpp>

TEST_CASE("should use a client", "[pool]") {
	paper::pool pool ("127.0.0.1", 3145, 2);

	auto client = pool.lock_client();
	auto response = client->ping();
	pool.unlock_client(client);

	REQUIRE(response->is_ok);
	REQUIRE(response->data == "pong");
}
