#include "../win/win.h"

namespace utils {
	void c_log_event_dispatcher::c_default_log_listener::process_event(e_log_type id, const std::unordered_map<std::string, std::any>& parameters) {
		switch(id) {
			case e_log_type::info: { std::cout << ((e_dye::blue | e_dye::intensity) << e_dye::on_background | e_dye::white) << "[info]" << e_dye::restore << " " << (e_dye::blue | e_dye::intensity) << std::any_cast<std::string>(parameters.at("text")) << e_dye::restore << std::endl; } break;
			case e_log_type::warning: { std::cout << (e_dye::yellow << e_dye::on_background | e_dye::white) << "[warning]" << e_dye::restore << " " << e_dye::yellow << std::any_cast<std::string>(parameters.at("text")) << e_dye::restore << std::endl; } break;
			case e_log_type::error: { std::cout << (e_dye::red << e_dye::on_background | e_dye::white) << "[error]" << e_dye::restore << " " << e_dye::red << std::any_cast<std::string>(parameters.at("text")) << e_dye::restore << std::endl; } break;
			case e_log_type::assert: { throw std::runtime_error{ std::any_cast<std::string>(parameters.at("text")) }; } break;
		}
	}
}