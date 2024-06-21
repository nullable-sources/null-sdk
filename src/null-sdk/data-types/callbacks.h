#pragma once
#include <functional>
#include <vector>
#include <algorithm>

namespace utils {
    template <auto, typename>
    struct callback_t { };

    template <auto place, typename result_t, typename ...args_t>
    struct callback_t<place, result_t(args_t...)> {
    private:
        using function_t = std::function<result_t(args_t...)>;
        function_t callback{ };

    public:
        void set(const function_t& _callback_t) { callback = _callback_t; }
        result_t call(args_t... args) { return callback(args...); }

        bool empty() const { return !callback; }

    public:
        operator bool() const { !empty(); }
    };

    template <auto, typename>
    struct callbacks_t { };

    template <auto place, typename result_t, typename ...args_t>
    struct callbacks_t<place, result_t(args_t...)> {
    private:
        using function_t = std::function<result_t(args_t...)>;
        std::vector<function_t> callbacks{ };

    public:
        auto add(const function_t& _callback_t) { callbacks.push_back(_callback_t); return std::prev(callbacks.end()); }
        void remove(const auto& iterator) { callbacks.erase(iterator); }

        template <typename result_t = result_t>
        std::enable_if_t<!std::is_same_v<result_t, void>, std::vector<result_t>> call(args_t... args) {
            std::vector<result_t> result{ };
            std::ranges::for_each(callbacks, [&](const function_t& callback) { result.push_back(callback(args...)); });
            return result;
        }

        template <typename result_t = result_t>
        std::enable_if_t<std::is_same_v<result_t, void>, void> call(args_t... args) {
            std::ranges::for_each(callbacks, [&](const function_t& callback) { callback(args...); });
        }

        bool empty() const { return callbacks.empty(); }

    public:
        operator bool() const { !empty(); }
    };

    template <class ...callback_t>
    struct callbacks_tuple_t {
    private:
        std::tuple<callback_t...> callbacks{ };

    public:
        template <auto place_t>
        auto& at() { return std::get<(int)place_t>(callbacks); }
    };
}