#ifndef _PAPER_CLIENT_HPP_
#define _PAPER_CLIENT_HPP_

#include <string>
#include <memory>
#include <paper_client_cpp/response.hpp>

extern "C" {
	#include <paper_client_c/client.h>
}

typedef std::unique_ptr<paper::response<std::string>> str_response_ptr;
typedef std::unique_ptr<paper::response<paper::stats>> stats_response_ptr;

namespace paper {
	class client;
};

class paper::client {
private:
	paper_client* c_client;

public:
	client(
		const std::string& host = "127.0.0.1",
		const int port = 3145
	) : c_client(paper_connect(host.c_str(), port)) {}

	~client();

	str_response_ptr ping();
	str_response_ptr version();
	str_response_ptr get(const std::string&);
	str_response_ptr set(
		const std::string&,
		const std::string&,
		const uint32_t& = 0
	);
	str_response_ptr del(const std::string&);
	str_response_ptr wipe();
	str_response_ptr resize(const uint64_t&);
	str_response_ptr policy(const paper::policy&);
	stats_response_ptr stats();

private:
	static str_response_ptr process_str_response(paper_str_response*);

	static paper_policy_t c_policy_from_policy(const paper::policy&);
	static paper::policy policy_from_c_policy(const paper_policy_t&);
};

#endif
