module;
#include <unordered_map>
#include <any>
#include <string>
#include <format>
#include <iostream>
export module null.sdk:utils.logger;

import :utils.events;
import :utils.win.console;

namespace utils {
    export enum class e_log_type { info, warning, error, assert };
    class c_log_listener : public i_event_listener<e_log_type> {
    public:
        void on_attach() override { }
        void process_event(e_log_type id, const std::unordered_map<std::string, std::any>& parameters) override {
            switch(id) {
                case e_log_type::info: { std::cout << ((e_dye::blue | e_dye::intensity) << e_dye::on_background | e_dye::white) << "[info]" << e_dye::restore << " " << (e_dye::blue | e_dye::intensity) << std::any_cast<std::string>(parameters.at("text")) << e_dye::restore << std::endl; } break;
            	case e_log_type::warning: { std::cout << (e_dye::yellow << e_dye::on_background | e_dye::white) << "[warning]" << e_dye::restore << " " << e_dye::yellow << std::any_cast<std::string>(parameters.at("text")) << e_dye::restore << std::endl; } break;
            	case e_log_type::error: { std::cout << (e_dye::red << e_dye::on_background | e_dye::white) << "[error]" << e_dye::restore << " " << e_dye::red << std::any_cast<std::string>(parameters.at("text")) << e_dye::restore << std::endl; } break;
            	case e_log_type::assert: { throw std::runtime_error{ std::any_cast<std::string>(parameters.at("text")) }; } break;
            }
        }
    } log_listener{ };

    export class c_log_dispatcher : public c_event_dispatcher<e_log_type> {
    public:
        c_log_dispatcher() {
            attach_listener(e_log_type::info, &log_listener);
            attach_listener(e_log_type::warning, &log_listener);
            attach_listener(e_log_type::error, &log_listener);
            attach_listener(e_log_type::assert, &log_listener);
        }

        ~c_log_dispatcher() {
            detach_listener(e_log_type::info, &log_listener);
            detach_listener(e_log_type::warning, &log_listener);
            detach_listener(e_log_type::error, &log_listener);
            detach_listener(e_log_type::assert, &log_listener);
        }

    public:
        template <typename... args_t>
        void log(e_log_type id, std::string_view str, args_t&&... args) {
            dispatch_event(id, { { "text", std::vformat(str, std::make_format_args(args...)) } });
        }

        template <typename... args_t>
        void operator()(e_log_type id, std::string_view str, args_t&&... args) { log(id, str, args...); }

        template <typename... args_t>
        void operator()(std::string_view str, args_t&&... args) { log(e_log_type::info, str, args...); }
    } logger{ };
}