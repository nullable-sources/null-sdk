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
	using callbacks_array_t = std::vector<std::any>; //@note: cant use std::map::mapped_type :(
	using callbacks_t = std::map<e_callbacks, callbacks_array_t>;
	callbacks_t callbacks{ };

public:
	array_callbacks_t() { }
	array_callbacks_t(const callbacks_t& _callbacks) : callbacks(_callbacks) { }

public:
	template <typename function_t>
	callbacks_array_t::iterator add(const e_callbacks& place, const std::function<function_t>& function) {
		callbacks[place].push_back(function);
		return std::prev(callbacks[place].end());
	}

	void remove(const e_callbacks& place, const callbacks_array_t::iterator& callback) { callbacks[place].erase(callback); }

	bool have_callbacks(const e_callbacks& place) {
		if(callbacks.empty() || callbacks[place].empty()) return false;
		return std::ranges::find_if(callbacks[place], [](const callbacks_array_t::value_type& callback) { return callback.has_value(); }) != callbacks[place].end();
	}

	bool empty() {
		if(callbacks.empty()) return true;
		return std::ranges::find_if(callbacks, [=](const callbacks_t::value_type& callback) { return have_callbacks(callback.first); }) == callbacks.end();
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<std::is_same_v<typename std::function<function_t>::result_type, void>, void> call(const e_callbacks& place, args_t ...args) {
		std::ranges::for_each(callbacks[place], [=](const std::any& callback) {
			if(callback.has_value())
				std::any_cast<std::function<function_t>>(callback)(args...);
			});
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<!std::is_same_v<typename std::function<function_t>::result_type, void>, callbacks_array_t> call(const e_callbacks& place, args_t ...args) {
		callbacks_array_t results{ };
		std::ranges::for_each(callbacks[place], [&](const std::any& callback) {
			if(callback.has_value())
				results.push_back(std::any_cast<std::function<function_t>>(callback)(args...));
			});
		return results;
	}
};

template <typename e_callbacks>
struct single_callbacks_t {
private:
	using callback_t = std::any;
	using callbacks_t = std::map<e_callbacks, callback_t>;
	callbacks_t callbacks{ };

public:
	single_callbacks_t() { }
	single_callbacks_t(const callbacks_t& _callbacks) : callbacks(_callbacks) { }

public:
	template <typename function_t>
	void set(const e_callbacks& place, const std::function<function_t>& function) { callbacks[place] = function; }
	void remove(const e_callbacks& place) { callbacks[place] = nullptr; }

	bool have_callback(const e_callbacks& place) { return !callbacks.empty() && callbacks[place].has_value(); }
	bool empty() {
		if(callbacks.empty()) return true;
		return std::ranges::find_if(callbacks, [](const callbacks_t::value_type& callback) { return callback.second.has_value(); }) == callbacks.end();
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<std::is_same_v<typename std::function<function_t>::result_type, void>, void> call(const e_callbacks& place, args_t ...args) {
		if(!have_callback(place)) return;
		std::any_cast<std::function<function_t>>(callbacks[place])(args...);
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<!std::is_same_v<typename std::function<function_t>::result_type, void>, callback_t> call(const e_callbacks& place, args_t ...args) {
		if(!have_callback(place)) return callback_t{ };
		return std::any_cast<std::function<function_t>>(callbacks[place])(args...);
	}
};