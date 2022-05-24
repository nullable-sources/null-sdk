#pragma once
#include <type_traits>
#include <functional>
#include <stdexcept>
#include <vector>
#include <map>
#include <any>

template <typename e_callbacks>
struct array_callbacks_t {
private:
	std::map<e_callbacks, std::vector<std::any>> callbacks{ };

public:
	template <typename function_t>
	std::vector<std::any>::iterator add(e_callbacks place, const std::function<function_t>& function) {
		callbacks[place].push_back(function);
		return std::prev(callbacks[place].end());
	}

	void remove(e_callbacks place, const std::vector<std::any>::iterator& callback) { callbacks[place].erase(callback); }

	bool have_callbacks(e_callbacks place) {
		if(callbacks.empty() || callbacks[place].empty()) return false;
		for(std::any& callback : callbacks[place]) if(callback.has_value()) return true;
		return false;
	}

	bool empty() {
		if(callbacks.empty()) return false;
		for(auto& [place, callbacks_list] : callbacks) {
			for(std::any& callback : callbacks_list) {
				if(callback.has_value()) return true;
			}
		}
		return false;
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<std::is_same_v<typename std::function<function_t>::result_type, void>, void> call(e_callbacks place, args_t ...args) {
		if(!have_callbacks(place)) throw std::runtime_error("callbacks empty");

		for(std::any& callback : callbacks[place]) {
			std::any_cast<std::function<function_t>>(callback)(args...);
		}
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<!std::is_same_v<typename std::function<function_t>::result_type, void>, std::vector<std::any>> call(e_callbacks place, args_t ...args) {
		if(!have_callbacks(place)) throw std::runtime_error("callbacks empty");
		
		std::vector<std::any> results{ };
		for(std::any& callback : callbacks[place]) {
			results.push_back(std::any_cast<std::function<function_t>>(callback)(args...));
		}
		return results;
	}
};

template <typename e_callbacks>
struct single_callbacks_t {
private:
	std::map<e_callbacks, std::any> callbacks{ };

public:
	template <typename function_t>
	void set(e_callbacks place, const std::function<function_t>& function) { callbacks[place] = function; }
	void remove(e_callbacks place) { callbacks[place] = nullptr; }

	bool have_callback(e_callbacks place) { return !callbacks.empty() && callbacks[place].has_value(); }
	bool empty() {
		if(callbacks.empty()) return false;
		for(auto& [place, callback] : callbacks) if(callback.has_value()) return true;
		return false;
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<std::is_same_v<typename std::function<function_t>::result_type, void>, void> call(e_callbacks place, args_t ...args) {
		if(!have_callback(place)) throw std::runtime_error("callback empty");
		std::any_cast<std::function<function_t>>(callbacks[place])(args...);
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<!std::is_same_v<typename std::function<function_t>::result_type, void>, std::any> call(e_callbacks place, args_t ...args) {
		if(!have_callback(place)) throw std::runtime_error("callback empty");
		return std::any_cast<std::function<function_t>>(callbacks[place])(args...);
	}
};