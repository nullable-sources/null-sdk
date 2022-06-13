#pragma once
#include <type_traits>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <map>
#include <any>

template <typename e_callbacks>
struct array_callbacks_t {
private:
	std::map<e_callbacks, std::vector<std::any>> callbacks{ };

public:
	template <typename function_t>
	std::vector<std::any>::iterator add(const e_callbacks& place, const std::function<function_t>& function) {
		callbacks[place].push_back(function);
		return std::prev(callbacks[place].end());
	}

	void remove(const e_callbacks& place, const std::vector<std::any>::iterator& callback) { callbacks[place].erase(callback); }

	bool have_callbacks(const e_callbacks& place) {
		if(callbacks.empty() || callbacks[place].empty()) return false;
		return std::ranges::find_if(callbacks[place], [](const auto& callback) { return callback.has_value(); }) != callbacks[place].end();
	}

	bool empty() {
		if(callbacks.empty()) return true;
		return std::ranges::find_if(callbacks, [=](const auto& callback) { return have_callbacks(callback.first); }) == callbacks.end();
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<std::is_same_v<typename std::function<function_t>::result_type, void>, void> call(const e_callbacks& place, args_t ...args) {
		std::ranges::for_each(callbacks[place], [=](const auto& callback) {
			if(callback.has_value())
				std::any_cast<std::function<function_t>>(callback)(args...);
			});
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<!std::is_same_v<typename std::function<function_t>::result_type, void>, std::vector<std::any>> call(const e_callbacks& place, args_t ...args) {
		std::vector<std::any> results{ };
		std::ranges::for_each(callbacks[place], [&](const auto& callback) {
			if(callback.has_value())
				results.push_back(std::any_cast<std::function<function_t>>(callback)(args...));
			});
		return results;
	}
};

template <typename e_callbacks>
struct single_callbacks_t {
private:
	std::map<e_callbacks, std::any> callbacks{ };

public:
	template <typename function_t>
	void set(const e_callbacks& place, const std::function<function_t>& function) { callbacks[place] = function; }
	void remove(const e_callbacks& place) { callbacks[place] = nullptr; }

	bool have_callback(const e_callbacks& place) { return !callbacks.empty() && callbacks[place].has_value(); }
	bool empty() {
		if(callbacks.empty()) return true;
		return std::ranges::find_if(callbacks, [](const auto& callback) { return callback.second.has_value(); }) == callbacks.end();
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<std::is_same_v<typename std::function<function_t>::result_type, void>, void> call(const e_callbacks& place, args_t ...args) {
		if(!have_callback(place)) return;
		std::any_cast<std::function<function_t>>(callbacks[place])(args...);
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<!std::is_same_v<typename std::function<function_t>::result_type, void>, std::any> call(const e_callbacks& place, args_t ...args) {
		if(!have_callback(place)) return std::any{ };
		return std::any_cast<std::function<function_t>>(callbacks[place])(args...);
	}
};