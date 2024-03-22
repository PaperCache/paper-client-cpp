#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <paper_client_cpp/pool.hpp>

bool can_set(paper::pool&);

TEST_CASE("should use a client", "[pool]") {
	paper::pool pool ("127.0.0.1", 3145, 2);

	auto client = pool.lock_client();
	auto response = client->ping();
	pool.unlock_client(client);

	REQUIRE(response->is_ok);
	REQUIRE(response->data == "pong");
}

TEST_CASE("should authorize all clients", "[pool::auth]") {
	paper::pool pool ("127.0.0.1", 3145, 2);

	REQUIRE(!can_set(pool));
	pool.auth("auth_token");
	REQUIRE(can_set(pool));
}


bool can_set(paper::pool& pool) {
	auto client = pool.lock_client();
	auto response = client->set("key", "value");
	pool.unlock_client(client);

	return response->is_ok;
}
