#pragma once
#include <iostream>
#include <format>
#include <utils/events/events.h>

namespace utils {
    enum class e_log_type { info, warning, error };
    class c_log_dispatcher : public c_event_dispatcher<e_log_type> {
    public:
        class c_default_log_listener : public i_event_listener<e_log_type> {
        public:
            void process_event(const e_log_type& id, const std::unordered_map<std::string, std::any>& parameters) override {
                switch(id) {
                    case e_log_type::info: { std::cout << "\033[3;104;30m" << "[info]" << "\033[0m " << "\x1B[36m" << std::any_cast<std::string>(parameters.at("text")) << "\033[0m" << std::endl; } break;
                    case e_log_type::warning: { std::cout << "\033[3;43;30m" << "[warning]" << "\033[0m " << "\x1B[33m" << std::any_cast<std::string>(parameters.at("text")) << "\033[0m" << std::endl; } break;
                    case e_log_type::error: { throw std::runtime_error{ std::format("\033[3;42;30m[error]\033[0m \x1B[31m{}\033[0m\n", std::any_cast<std::string>(parameters.at("text"))) }; } break;
                }
            }
        } default_listener{ };

    public:
        c_log_dispatcher() {
            attach_listener(e_log_type::info, &default_listener);
            attach_listener(e_log_type::warning, &default_listener);
            attach_listener(e_log_type::error, &default_listener);
        }

    public:
        template <typename... args_t>
        void log(const e_log_type& id, const std::string_view& str, args_t&&... args) { dispatch_event(id, { { "text", std::vformat(str, std::make_format_args(args...)) } }); }
    } inline logger{ };
}