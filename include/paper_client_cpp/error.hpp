/*
 * Copyright (c) Kia Shakiba
 *
 * This source code is licensed under the GNU AGPLv3 license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef _PAPER_ERROR_HPP_
#define _PAPER_ERROR_HPP_

extern "C" {
	#include <paper_client_c/error.h>
}

namespace paper {
	enum error {
		INTERNAL = PAPER_INTERNAL,

		UNREACHABLE_SERVER = PAPER_UNREACHABLE_SERVER,
		MAX_CONNECTIONS_EXCEEDED = PAPER_MAX_CONNECTIONS_EXCEEDED,
		UNAUTHORIZED = PAPER_UNAUTHORIZED,

		KEY_NOT_FOUND = PAPER_KEY_NOT_FOUND,

		ZERO_VALUE_SIZE = PAPER_ZERO_VALUE_SIZE,
		EXCEEDING_VALUE_SIZE = PAPER_EXCEEDING_VALUE_SIZE,

		ZERO_CACHE_SIZE = PAPER_ZERO_CACHE_SIZE,

		UNCONFIGURED_POLICY = PAPER_UNCONFIGURED_POLICY,
		INVALID_POLICY = PAPER_INVALID_POLICY,
	};
}

#endif
