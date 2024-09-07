#include "../win/win.h"

namespace ntl::sdk {
    void c_log_event_dispatcher::c_console_log_listener::process_event(e_log_type id, const event_parameters_t& parameters) {
        constexpr e_dye info_text_color = e_dye::blue | e_dye::intensity;
        constexpr e_dye info_title_color = info_text_color << e_dye::on_background | e_dye::white;

        constexpr e_dye warning_text_color = e_dye::yellow;
        constexpr e_dye warning_title_color = warning_text_color << e_dye::on_background | e_dye::white;

        constexpr e_dye error_text_color = e_dye::red;
        constexpr e_dye error_title_color = error_text_color << e_dye::on_background | e_dye::white;

        const std::string& log_text = std::any_cast<const std::string&>(parameters.at("text"));
        switch(id) {
            case e_log_type::info: { std::cout << info_title_color << "[info]" << e_dye::restore << " " << info_text_color << log_text << e_dye::restore << std::endl; } break;
            case e_log_type::warning: { std::cout << warning_title_color << "[warning]" << e_dye::restore << " " << warning_text_color << log_text << e_dye::restore << std::endl; } break;
            case e_log_type::error: { std::cout << error_title_color << "[error]" << e_dye::restore << " " << error_text_color << log_text << e_dye::restore << std::endl; } break;
            case e_log_type::assert: { throw std::runtime_error(log_text); } break;
        }
    }
}