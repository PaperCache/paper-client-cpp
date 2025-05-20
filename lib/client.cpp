#include <stdexcept>
#include <paper_client_cpp/response.hpp>
#include <paper_client_cpp/client.hpp>

paper::client::~client() {
	paper_disconnect(this->c_client);
}

paper_client* paper::client::get_c_client() {
	return this->c_client;
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

response_ptr paper::client::auth(const std::string& key) {
	return paper::client::process_response(
		paper_auth(this->c_client, key.c_str())
	);
}

str_response_ptr paper::client::get(const std::string& key) {
	return paper::client::process_str_response(
		paper_get(this->c_client, key.c_str())
	);
}

response_ptr paper::client::set(
	const std::string& key,
	const std::string& value,
	const uint32_t ttl
) {
	return paper::client::process_response(
		paper_set(this->c_client, key.c_str(), value.c_str(), ttl)
	);
}

response_ptr paper::client::del(const std::string& key) {
	return paper::client::process_response(
		paper_del(this->c_client, key.c_str())
	);
}

has_response_ptr paper::client::has(const std::string& key) {
	paper_has_response* has_response = paper_has(this->c_client, key.c_str());

	auto response = has_response_ptr(new paper::data_response<bool>(
		has_response->is_ok,
		has_response->has,
		paper::client::error_from_c_error(has_response->error)
	));

	paper_has_response_free(has_response);

	return response;
}

str_response_ptr paper::client::peek(const std::string& key) {
	return paper::client::process_str_response(
		paper_peek(this->c_client, key.c_str())
	);
}

response_ptr paper::client::ttl(const std::string& key, const uint32_t ttl) {
	return paper::client::process_response(
		paper_ttl(this->c_client, key.c_str(), ttl)
	);
}

size_response_ptr paper::client::size(const std::string& key) {
	paper_size_response* size_response = paper_size(this->c_client, key.c_str());

	auto response = size_response_ptr(new paper::data_response<uint32_t>(
		size_response->is_ok,
		size_response->size,
		paper::client::error_from_c_error(size_response->error)
	));

	paper_size_response_free(size_response);

	return response;
}

response_ptr paper::client::wipe() {
	return paper::client::process_response(
		paper_wipe(this->c_client)
	);
}

response_ptr paper::client::resize(const uint64_t size) {
	return paper::client::process_response(
		paper_resize(this->c_client, size)
	);
}

response_ptr paper::client::policy(const std::string& policy) {
	return paper::client::process_response(
		paper_policy(this->c_client, policy.c_str())
	);
}

stats_response_ptr paper::client::stats() {
	paper_stats_response* stats_response = paper_stats(this->c_client);
	std::vector<std::string> policies;

	for (uint32_t i=0; i<stats_response->stats.num_policies; i++) {
		policies.push_back(std::string(stats_response->stats.policies[i]));
	}

	paper::stats stats {
		stats_response->stats.max_size,
		stats_response->stats.used_size,
		stats_response->stats.num_objects,

		stats_response->stats.total_gets,
		stats_response->stats.total_sets,
		stats_response->stats.total_dels,

		stats_response->stats.miss_ratio,

		policies,
		std::string(stats_response->stats.policy),
		stats_response->stats.is_auto_policy,

		stats_response->stats.uptime
	};

	auto response = stats_response_ptr(new paper::data_response<paper::stats>(
		stats_response->is_ok,
		stats,
		paper::client::error_from_c_error(stats_response->error)
	));

	paper_stats_response_free(stats_response);

	return response;
}

response_ptr paper::client::process_response(paper_response* paper_response) {
	auto response = response_ptr(new paper::response(
		paper_response->is_ok,
		paper::client::error_from_c_error(paper_response->error)
	));

	paper_response_free(paper_response);

	return response;
}

str_response_ptr paper::client::process_str_response(paper_str_response* paper_str_response) {
	auto response = str_response_ptr(new paper::data_response<std::string>(
		paper_str_response->is_ok,
		paper_str_response->is_ok ? std::string(paper_str_response->data) : std::string(),
		paper::client::error_from_c_error(paper_str_response->error)
	));

	paper_str_response_free(paper_str_response);

	return response;
}

paper::error paper::client::error_from_c_error(const paper_error_t& error) {
	switch (error) {
		case PAPER_UNREACHABLE_SERVER: return paper::error::UNREACHABLE_SERVER;
		case PAPER_MAX_CONNECTIONS_EXCEEDED: return paper::error::MAX_CONNECTIONS_EXCEEDED;
		case PAPER_UNAUTHORIZED: return paper::error::UNAUTHORIZED;

		case PAPER_KEY_NOT_FOUND: return paper::error::KEY_NOT_FOUND;

		case PAPER_ZERO_VALUE_SIZE: return paper::error::ZERO_VALUE_SIZE;
		case PAPER_EXCEEDING_VALUE_SIZE: return paper::error::EXCEEDING_VALUE_SIZE;

		case PAPER_ZERO_CACHE_SIZE: return paper::error::ZERO_CACHE_SIZE;

		default: return paper::error::INTERNAL;
	}
}
