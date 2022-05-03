//original - https://github.com/Neargye/magic_enum/tree/v0.5.0
export module null.sdk:utils.enum_reflection;
import std.core;

export namespace utils::enum_reflection {
    template <typename enum_t>
    struct range final {
        static constexpr int min = std::is_signed_v<std::underlying_type_t<enum_t>> ? -128 : 0;
        static constexpr int max = 128;
    };

    namespace impl {
        template <typename enum_t>
        constexpr int min() {
            using u_enum_t = std::underlying_type_t<enum_t>;
            return range<enum_t>::min > (std::numeric_limits<u_enum_t>::min)() ? range<enum_t>::min : (std::numeric_limits<u_enum_t>::min)();
        }

        template <typename enum_t>
        constexpr int max() {
            using u_enum_t = std::underlying_type_t<enum_t>;
            return range<enum_t>::max < (std::numeric_limits<u_enum_t>::max)() ? range<enum_t>::max : (std::numeric_limits<u_enum_t>::max)();
        }

        template <typename enum_t>
        constexpr auto range() {
            return std::make_integer_sequence<int, max<enum_t>() - min<enum_t>() + 1>{ };
        }

        template <typename enum_t, enum_t value>
        constexpr const std::string_view name() noexcept {
#if defined(__clang__)
            constexpr std::string_view name{ __PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 2 };
#elif defined(__GNUC__) && __GNUC__ >= 9
            constexpr std::string_view name{ __PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 51 };
#elif defined(_MSC_VER)
            constexpr std::string_view name{ __FUNCSIG__, sizeof(__FUNCSIG__) - 17 };
#else
            return {}; // unsupported compiler.
#endif

            constexpr auto prefix = name.find_last_of(" :,-)") + 1;

            if constexpr(name[prefix] >= '0' && name[prefix] <= '9') return {};
            else return name.substr(prefix, name.length() - prefix);
        }

        template <typename enum_t, int... sequence>
        constexpr auto strings(std::integer_sequence<int, sequence...>) noexcept {
            return std::array<std::string_view, sizeof...(sequence)>{ { name<enum_t, static_cast<enum_t>(sequence + min<enum_t>())>()... } };
        }

        template <typename enum_t>
        constexpr std::string_view name(int value) noexcept {
            constexpr auto names = strings<enum_t>(range<enum_t>());

            if(int i = value - min<enum_t>(); i >= 0 && static_cast<std::size_t>(i) < names.size()) return std::string_view{ names[i] };
            else return {};
        }

        template <typename enum_t, int... sequence>
        constexpr auto values(std::integer_sequence<int, sequence...>) noexcept {
            constexpr int n = sizeof...(sequence);
            constexpr std::array<bool, n> valid{ {!name<enum_t, static_cast<enum_t>(sequence + min<enum_t>())>().empty()...} };
            constexpr int num_valid = ((valid[sequence] ? 1 : 0) + ...);

            std::array<enum_t, num_valid> values{};
            for(int i = 0, v = 0; i < n && v < num_valid; ++i) {
                if(valid[i]) {
                    values[v++] = static_cast<enum_t>(i + min<enum_t>());
                }
            }

            return values;
        }

        template <typename enum_t, std::size_t... sequence>
        constexpr auto names(std::integer_sequence<std::size_t, sequence...>) noexcept {
            return std::array<std::string_view, sizeof...(sequence)>{ { name<enum_t, values<enum_t>(range<enum_t>())[sequence]>()... } };
        }
    }

    template <typename enum_t, typename = std::decay_t<enum_t>>
    constexpr auto count() noexcept {
        return impl::values<std::decay_t<enum_t>>(impl::range<std::decay_t<enum_t>>()).size();
    }

    template <auto value, typename = std::decay_t<decltype(value)>>
    constexpr std::string_view name() noexcept {
        return impl::name<std::decay_t<decltype(value)>, value>();
    }

    template <typename enum_t, typename = std::decay_t<enum_t>>
    constexpr std::string_view name(enum_t value) noexcept {
        return impl::name<std::decay_t<enum_t>>(static_cast<int>(value));
    }

    template <typename enum_t, typename = std::decay_t<enum_t>>
    constexpr auto names() noexcept {
        return impl::names<std::decay_t<enum_t>>(std::make_index_sequence<count<enum_t>()>{});
    }
}