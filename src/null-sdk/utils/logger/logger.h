#pragma once
#include <iostream>
#include <format>
#include "../events/events.h"

namespace ntl::utils {
    enum class e_log_type { info, warning, error, assert };
    class c_log_event_dispatcher : public c_event_dispatcher<e_log_type> {
    public:
        class c_default_log_listener : public i_event_listener<e_log_type> {
        public:
            void process_event(e_log_type id, const event_parameters_t& parameters) override;
        } default_listener{ };

    public:
        c_log_event_dispatcher() {
            attach_listener(e_log_type::info, &default_listener);
            attach_listener(e_log_type::warning, &default_listener);
            attach_listener(e_log_type::error, &default_listener);
            attach_listener(e_log_type::assert, &default_listener);
        }

        ~c_log_event_dispatcher() {
            detach_listener(e_log_type::info, &default_listener);
            detach_listener(e_log_type::warning, &default_listener);
            detach_listener(e_log_type::error, &default_listener);
            detach_listener(e_log_type::assert, &default_listener);
        }

    public:
        template <typename... args_t>
        void operator()(e_log_type id, std::string_view str, args_t&&... args) {
            dispatch_event(id, { { "text", std::vformat(str, std::make_format_args(args...)) } });
        }
    } inline logger{ };
}