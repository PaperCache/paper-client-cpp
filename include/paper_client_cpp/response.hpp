#ifndef _PAPER_RESPONSE_HPP_
#define _PAPER_RESPONSE_HPP_

#include <string>

extern "C" {
	#include <paper_client_c/response.h>
}

namespace paper {
	enum policy {
		LFU = PAPER_LFU,
		FIFO = PAPER_FIFO,
		LRU = PAPER_LRU,
		MRU = PAPER_MRU,
	};

	struct stats {
		const uint64_t max_size;
		const uint64_t used_size;

		const uint64_t total_gets;
		const uint64_t total_sets;
		const uint64_t total_dels;

		const double miss_ratio;

		const paper::policy policy;
		const uint64_t uptime;
	};

	template <typename T>
	struct response {
		bool is_ok;
		T data;

		response(bool is_ok, T data) :
			is_ok(is_ok), data(data) {}
	};

	template <>
	struct response<bool> {
		bool is_ok;
		bool data;
		std::string err_data;

		response(bool is_ok, bool data, char* err_data) :
			is_ok(is_ok), data(data)
		{
			if (err_data != NULL) {
				this->err_data = std::string(err_data);
			}
		}
	};

	template <>
	struct response<uint64_t> {
		bool is_ok;
		uint64_t data;
		std::string err_data;

		response(bool is_ok, uint64_t data, char* err_data) :
			is_ok(is_ok), data(data)
		{
			if (err_data != NULL) {
				this->err_data = std::string(err_data);
			}
		}
	};

	template <>
	struct response<paper::stats> {
		bool is_ok;
		paper::stats stats;
		std::string err_data;

		response(bool is_ok, paper::stats stats, char* err_data) :
			is_ok(is_ok), stats(stats)
		{
			if (err_data != NULL) {
				this->err_data = std::string(err_data);
			}
		}
	};
};

#endif
