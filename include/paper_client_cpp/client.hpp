#ifndef _PAPER_CLIENT_HPP_
#define _PAPER_CLIENT_HPP_

#include <string>
#include <memory>
#include <stdexcept>
#include <paper_client_cpp/response.hpp>

extern "C" {
	#include <paper_client_c/client.h>
}

typedef std::unique_ptr<paper::response> response_ptr;
typedef std::unique_ptr<paper::data_response<std::string>> str_response_ptr;
typedef std::unique_ptr<paper::data_response<bool>> has_response_ptr;
typedef std::unique_ptr<paper::data_response<uint32_t>> size_response_ptr;
typedef std::unique_ptr<paper::data_response<paper::stats>> stats_response_ptr;

namespace paper {
	class client;
};

class paper::client {
private:
	paper_client* c_client;

public:
	client(paper_client* c_client) : c_client(c_client) {}

	client(const std::string& paper_addr = "paper://127.0.0.1:3145") {
		paper_client* client = paper_connect(paper_addr.c_str());

		if (client == NULL) {
			throw std::runtime_error("Could not connect to PaperCache.");
		}

		this->c_client = client;
	}

	~client();

	paper_client* get_c_client();

	str_response_ptr ping();
	str_response_ptr version();

	response_ptr auth(const std::string&);

	str_response_ptr get(const std::string&);
	response_ptr set(
		const std::string&,
		const std::string&,
		const uint32_t = 0
	);
	response_ptr del(const std::string&);

	has_response_ptr has(const std::string&);
	str_response_ptr peek(const std::string&);
	response_ptr ttl(const std::string&, const uint32_t = 0);
	size_response_ptr size(const std::string&);

	response_ptr wipe();
	response_ptr resize(const uint64_t);

	response_ptr policy(const std::string&);
	stats_response_ptr stats();

private:
	static response_ptr process_response(paper_response*);
	static str_response_ptr process_str_response(paper_str_response*);

	static paper::error error_from_c_error(const paper_error_t&);
};

#endif
