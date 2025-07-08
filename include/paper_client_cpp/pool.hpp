/*
 * Copyright (c) Kia Shakiba
 *
 * This source code is licensed under the GNU AGPLv3 license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef _PAPER_POOL_HPP_
#define _PAPER_POOL_HPP_

#include <string>
#include <paper_client_cpp/client.hpp>

extern "C" {
	#include <paper_client_c/pool.h>
}

namespace paper {
	class pool;
};

class paper::pool {
private:
	paper_pool* c_pool;

public:
	pool(
		const std::string& paper_addr = "paper://127.0.0.1:3145",
		const int size = 2
	): c_pool(paper_pool_connect(paper_addr.c_str(), size)) {}

	~pool();

	void auth(const std::string&);

	paper::client* lock_client();
	void unlock_client(paper::client* client);
};

#endif
