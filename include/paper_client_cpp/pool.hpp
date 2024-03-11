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
		const std::string& host = "127.0.0.1",
		const int port = 3145,
		const int size = 2
	): c_pool(paper_pool_connect(host.c_str(), port, size)) {}

	~pool();

	paper::client* lock_client();
	void unlock_client(paper::client* client);
};

#endif
