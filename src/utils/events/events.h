#pragma once
#include <string>
#include <unordered_map>
#include <any>

namespace utils {
	template <typename event_id_t>
	struct i_event_listener {
	public:
		virtual void on_attach() { }
		virtual void on_detach() { }
		virtual void process_event(event_id_t id, const std::unordered_map<std::string, std::any>& parameters) = 0;
	};

	template <typename event_id_t>
	class c_event_dispatcher {
	public:
		std::unordered_map<event_id_t, std::vector<i_event_listener<event_id_t>*>> listeners{ };

	public:
		virtual void attach_listener(event_id_t id, i_event_listener<event_id_t>* listener) { listeners[id].push_back(listener); listener->on_attach(); }
		virtual void detach_listener(event_id_t id, i_event_listener<event_id_t>* listener) {
			if(auto finded{ std::ranges::find(listeners[id], listener) }; finded != listeners[id].end()) {
				(*finded)->on_detach();
				listeners[id].erase(finded);
			}
		}

		virtual void dispatch_event(event_id_t id, const std::unordered_map<std::string, std::any>& parameters) {
			for(i_event_listener<event_id_t>* listener : listeners[id]) listener->process_event(id, parameters);
		}
	};
}