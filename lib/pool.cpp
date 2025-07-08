/*
 * Copyright (c) Kia Shakiba
 *
 * This source code is licensed under the GNU AGPLv3 license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <paper_client_cpp/pool.hpp>
#include <paper_client_cpp/client.hpp>

paper::pool::~pool() {
	paper_pool_disconnect(this->c_pool);
}

void paper::pool::auth(const std::string& token) {
	paper_pool_auth(this->c_pool, token.c_str());
}

paper::client* paper::pool::lock_client() {
	paper_client* client = paper_pool_client_lock(this->c_pool);
	return new paper::client(client);
}

void paper::pool::unlock_client(paper::client* client) {
	paper_pool_client_unlock(this->c_pool, client->get_c_client());
	free(client);
}
