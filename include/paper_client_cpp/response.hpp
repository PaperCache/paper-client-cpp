#ifndef _PAPER_RESPONSE_HPP_
#define _PAPER_RESPONSE_HPP_

#include <vector>
#include <paper_client_cpp/error.hpp>

extern "C" {
	#include <paper_client_c/response.h>
}

namespace paper {
	struct stats {
		const uint64_t max_size;
		const uint64_t used_size;
		const uint64_t num_objects;

		const uint64_t total_gets;
		const uint64_t total_sets;
		const uint64_t total_dels;

		const double miss_ratio;

		const std::vector<std::string> policies;
		const std::string policy;
		const bool is_auto_policy;

		const uint64_t uptime;
	};

	struct response {
		bool is_ok;
		paper::error error;

		response(bool is_ok, paper::error error) :
			is_ok(is_ok), error(error) {}
	};

	template <typename T>
	struct data_response {
		bool is_ok;
		T data;
		paper::error error;

		data_response(bool is_ok, T data, paper::error error) :
			is_ok(is_ok), data(data), error(error) {}
	};

	template <>
	struct data_response<bool> {
		bool is_ok;
		bool data;
		paper::error error;

		data_response(bool is_ok, bool data, paper::error error) :
			is_ok(is_ok), data(data), error(error) {}
	};

	template <>
	struct data_response<uint64_t> {
		bool is_ok;
		uint64_t data;
		paper::error error;

		data_response(bool is_ok, uint64_t data, paper::error error) :
			is_ok(is_ok), data(data), error(error) {}
	};

	template <>
	struct data_response<paper::stats> {
		bool is_ok;
		paper::stats stats;
		paper::error error;

		data_response(bool is_ok, paper::stats stats, paper::error error) :
			is_ok(is_ok), stats(stats), error(error) {}
	};
};

#endif
