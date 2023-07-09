#include <stdexcept>
#include <paper_client_cpp/client.hpp>

paper::client::~client() {
	paper_disconnect(this->c_client);
}

str_response_ptr paper::client::ping() {
	return paper::client::process_str_response(
		paper_ping(this->c_client)
	);
}

str_response_ptr paper::client::version() {
	return paper::client::process_str_response(
		paper_version(this->c_client)
	);
}

str_response_ptr paper::client::get(const std::string& key) {
	return paper::client::process_str_response(
		paper_get(this->c_client, key.c_str())
	);
}

str_response_ptr paper::client::set(
	const std::string& key,
	const std::string& value,
	const uint32_t& ttl
) {
	return paper::client::process_str_response(
		paper_set(this->c_client, key.c_str(), value.c_str(), ttl)
	);
}

str_response_ptr paper::client::del(const std::string& key) {
	return paper::client::process_str_response(
		paper_del(this->c_client, key.c_str())
	);
}

str_response_ptr paper::client::wipe() {
	return paper::client::process_str_response(
		paper_wipe(this->c_client)
	);
}

str_response_ptr paper::client::resize(const uint64_t& size) {
	return paper::client::process_str_response(
		paper_resize(this->c_client, size)
	);
}

str_response_ptr paper::client::policy(const paper::policy& policy) {
	auto c_policy = paper::client::c_policy_from_policy(policy);

	return paper::client::process_str_response(
		paper_policy(this->c_client, c_policy)
	);
}

stats_response_ptr paper::client::stats() {
	paper_stats_response* stats_response = paper_stats(this->c_client);

	paper::stats stats {
		stats_response->stats.max_size,
		stats_response->stats.used_size,
		stats_response->stats.total_gets,
		stats_response->stats.miss_ratio,
		paper::client::policy_from_c_policy(stats_response->stats.policy),
		stats_response->stats.uptime
	};

	auto response = stats_response_ptr(new paper::response<paper::stats>(
		stats_response->is_ok,
		stats
	));

	paper_stats_response_free(stats_response);

	return response;
}

str_response_ptr paper::client::process_str_response(paper_str_response* str_response) {
	auto response = str_response_ptr(new paper::response<std::string>(
		str_response->is_ok,
		std::string(str_response->data)
	));

	paper_str_response_free(str_response);

	return response;
}

paper_policy_t paper::client::c_policy_from_policy(const paper::policy& policy) {
	switch (policy) {
		case paper::policy::LFU: return PAPER_LFU;
		case paper::policy::FIFO: return PAPER_FIFO;
		case paper::policy::LRU: return PAPER_LRU;
		case paper::policy::MRU: return PAPER_MRU;
	}

	throw std::invalid_argument("Invalid paper policy.");
}

paper::policy paper::client::policy_from_c_policy(const paper_policy_t& c_policy) {
	switch (c_policy) {
		case PAPER_LFU: return paper::policy::LFU;
		case PAPER_FIFO: return paper::policy::FIFO;
		case PAPER_LRU: return paper::policy::LRU;
		case PAPER_MRU: return paper::policy::MRU;
	}

	throw std::invalid_argument("Invalid paper policy.");
}
