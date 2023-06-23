#ifndef _PAPER_RESPONSE_HPP_
#define _PAPER_RESPONSE_HPP_

extern "C" {
	#include <paper_client_c/response.h>
}

namespace paper {
	enum policy {
		LRU = PAPER_LRU,
		MRU = PAPER_MRU,
	};

	struct stats {
		const uint64_t max_size;
		const uint64_t used_size;
		const uint64_t total_gets;
		const double miss_ratio;
		const paper::policy policy;
	};

	template <typename T>
	struct response {
		bool is_ok;
		T data;

		response(bool is_ok, T data) :
			is_ok(is_ok), data(data) {}
	};

	struct str_response {
		bool is_ok;
		std::string data;
	};

	struct stats_response {
		bool is_ok;
		paper::stats stats;
	};
};

#endif
