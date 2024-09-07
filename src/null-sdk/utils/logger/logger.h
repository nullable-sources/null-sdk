#pragma once
#include <iostream>
#include <format>
#include "../events/events.h"

namespace ntl::sdk {
    enum class e_log_type { info, warning, error, assert };
    class c_log_event_dispatcher : public c_event_dispatcher<e_log_type> {
    public:
        class c_console_log_listener : public i_event_listener<e_log_type> {
        public:
            void process_event(e_log_type id, const event_parameters_t& parameters) override;
        } console_listener{ };

    public:
        c_log_event_dispatcher() {
            attach_listener(e_log_type::info, &console_listener);
            attach_listener(e_log_type::warning, &console_listener);
            attach_listener(e_log_type::error, &console_listener);
            attach_listener(e_log_type::assert, &console_listener);
        }

        ~c_log_event_dispatcher() {
            detach_listener(e_log_type::info, &console_listener);
            detach_listener(e_log_type::warning, &console_listener);
            detach_listener(e_log_type::error, &console_listener);
            detach_listener(e_log_type::assert, &console_listener);
        }

    public:
        template <typename... args_t>
        void operator()(e_log_type id, std::string_view str, args_t&&... args) {
            dispatch_event(id, { { "text", std::vformat(str, std::make_format_args(args...)) } });
        }

        template <typename... args_t>
        void operator()(e_log_type id, const event_parameters_t& parameters) {
            dispatch_event(id, parameters);
        }
    } inline logger{ };
}