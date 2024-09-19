#ifndef _PAPER_POLICY_HPP_
#define _PAPER_POLICY_HPP_

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
}

#endif
