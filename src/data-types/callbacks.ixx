export module null.sdk:data_types.callbacks;
import std.core;

export template <typename e_callbacks>
struct array_callbacks_t {
private:
	std::map<e_callbacks, std::vector<std::any>> callbacks{ };

public:
	template <typename function_t>
	std::vector<std::any>::iterator add(e_callbacks place, std::function<function_t> function) {
		callbacks[place].push_back(function);
		return callbacks[place].end() - 1;
	}

	void remove(e_callbacks place, std::vector<std::any>::iterator callback) { callbacks[place].erase(callback); }

	template <typename function_t, typename ...args_t>
	std::enable_if_t<std::is_same_v<typename std::function<function_t>::result_type, void>, void> call(e_callbacks place, args_t ...args) {
		for(std::any& callback : callbacks[place]) {
			if(!callback.has_value()) throw std::runtime_error("callback empty");
			std::any_cast<std::function<function_t>>(callback)(args...);
		}
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<!std::is_same_v<typename std::function<function_t>::result_type, void>, std::vector<std::any>> call(e_callbacks place, args_t ...args) {
		std::vector<std::any> results{ };
		for(std::any& callback : callbacks[place]) {
			if(!callback.has_value()) throw std::runtime_error("callback empty");
			results.push_back(std::any_cast<std::function<function_t>>(callback)(args...));
		}
		return results;
	}
};

export template <typename e_callbacks>
struct single_callbacks_t {
private:
	std::map<e_callbacks, std::any> callbacks{ };

public:
	template <typename function_t>
	void set(e_callbacks place, std::function<function_t> function) { callbacks[place] = function; }
	void remove(e_callbacks place) { callbacks[place] = nullptr; }

	template <typename function_t, typename ...args_t>
	std::enable_if_t<std::is_same_v<typename std::function<function_t>::result_type, void>, void> call(e_callbacks place, args_t ...args) {
		if(!callbacks[place].has_value()) throw std::runtime_error("callback empty");
		std::any_cast<std::function<function_t>>(callbacks[place])(args...);
	}

	template <typename function_t, typename ...args_t>
	std::enable_if_t<!std::is_same_v<typename std::function<function_t>::result_type, void>, std::any> call(e_callbacks place, args_t ...args) {
		if(!callbacks[place].has_value()) throw std::runtime_error("callback empty");
		return std::any_cast<std::function<function_t>>(callbacks[place])(args...);
	}
};