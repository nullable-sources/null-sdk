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
	array_callbacks_t(const callbacks_t& _callbacks) : callbacks{ _callbacks } { }

public:
	callbacks_array_t::iterator add(const e_callbacks& place, const auto& function) {
		callbacks[place].push_back(std::function{ function });
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

	template <typename ...args_t>
	void call(const e_callbacks& place, args_t ...args) {
		std::ranges::for_each(callbacks[place], [=](const std::any& callback) {
			if(callback.has_value()) std::any_cast<std::function<void(args_t...)>>(callback)(args...);
			});
	}

	template <typename return_t, typename ...args_t>
	std::vector<return_t> call(const e_callbacks& place, args_t ...args) {
		std::vector<return_t> results{ };
		std::ranges::for_each(callbacks[place], [&](const std::any& callback) {
			if(callback.has_value()) results.push_back(std::any_cast<std::function<return_t(args_t...)>>(callback)(args...));
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
	single_callbacks_t(const callbacks_t& _callbacks) : callbacks{ _callbacks } { }

public:
	void set(const e_callbacks& place, const auto& function) { callbacks[place] = std::function{ function }; }
	void remove(const e_callbacks& place) { callbacks[place] = nullptr; }

	bool have_callback(const e_callbacks& place) { return !callbacks.empty() && callbacks[place].has_value(); }
	bool empty() {
		if(callbacks.empty()) return true;
		return std::ranges::find_if(callbacks, [](const callbacks_t::value_type& callback) { return callback.second.has_value(); }) == callbacks.end();
	}

	template <typename ...args_t>
	void call(const e_callbacks& place, args_t ...args) {
		if(have_callback(place)) std::any_cast<std::function<void(args_t...)>>(callbacks[place])(args...);
	}

	template <typename return_t, typename ...args_t>
	return_t call(const e_callbacks& place, args_t ...args) {
		if(!have_callback(place)) return return_t{ };
		return std::any_cast<std::function<return_t(args_t...)>>(callbacks[place])(args...);
	}
};