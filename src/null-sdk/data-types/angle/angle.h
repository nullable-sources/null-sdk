#pragma once
#include <numbers>
#include <cmath>
#include <algorithm>

#include "../../utils/fast-operators.h"

using radians_t = double;
using degrees_t = float;

namespace ntl::literals {
    inline constexpr radians_t operator""rad(long double radians) { return radians; }
    inline constexpr degrees_t operator""deg(long double degrees) { return degrees; }
}

namespace ntl::sdk {
    template <typename value_t>
    concept is_angle_type_t = std::is_same_v<value_t, degrees_t> || std::is_same_v<value_t, radians_t>;

    template <is_angle_type_t value_t>
    class i_angle {
    public:
        value_t angle{ };

    public:
        inline constexpr i_angle() { }
        inline constexpr i_angle(value_t _angle) : angle{ _angle } { }

    public:
        template <typename self_t> inline constexpr operator value_t(this self_t&& self) { return self.angle; }

        NULLSDK_FAST_OPS_STRUCTURE_ALL_PREFIX_OPERATORS(inline constexpr, angle);
        NULLSDK_FAST_OPS_STRUCTURE_ALL_POSTFIX_OPERATORS(inline constexpr, angle);

        NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, const i_angle<value_t>&, RHS_FIELD, angle);
        NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, value_t, RHS_VALUE, angle);

        inline constexpr auto operator<=>(const i_angle<value_t>&) const = default;
        inline constexpr auto operator<=>(const value_t& other) const { return angle <=> other; }
    };
}

#define NULLSDK_ANGLE_IMPL_MAKE_FUNCTIONS(return_t, name)   \
    return_t name() const;                                  \
    return_t a##name() const;                               \
    return_t name##h() const;                               \
    return_t a##name##h() const;                            \

template <ntl::sdk::is_angle_type_t value_t>
struct angle_t { };

template <>
struct angle_t<radians_t> : public ntl::sdk::i_angle<radians_t> {
public:
    static constexpr double pi = 180. / std::numbers::pi;
    static constexpr radians_t maximal_boundires = std::numbers::pi * 2.;
    static constexpr radians_t minimal_boundires = maximal_boundires * -1.;

public:
    static angle_t<radians_t> atan2(auto y, auto x) { return angle_t<radians_t>((radians_t)std::atan2(y, x)); }

public:
    inline constexpr angle_t() { }
    inline constexpr angle_t(radians_t radians) : i_angle(radians) { }
    inline constexpr angle_t(degrees_t degrees);
    inline constexpr angle_t(const i_angle<radians_t>& _angle) : i_angle(_angle) { }
    inline constexpr angle_t(const i_angle<degrees_t>& degrees);
    inline constexpr angle_t(const angle_t<degrees_t>& degrees);

public:
    template <radians_t min = minimal_boundires, radians_t max = maximal_boundires>
    angle_t<radians_t> clamped() const { return std::clamp(angle, min, max); }

    template <radians_t min = minimal_boundires, radians_t max = maximal_boundires, typename self_t>
    auto&& clamp(this self_t&& self) { self = self.clamped<min, max>(); return self; }

    template <radians_t min = minimal_boundires, radians_t max = maximal_boundires>
    angle_t<radians_t> normalized() const {
        static constexpr auto constexpr_abs = [](auto val) { return val < 0 ? -val : val; };
        constexpr auto boundaries = constexpr_abs(min - max);
        return radians_t(angle - boundaries * std::floor((angle + (boundaries - max)) * (1. / boundaries)));
    }

    template <radians_t boundires, typename self_t>
    auto&& normalize(this self_t&& self) { self = self.normalized<boundires>(); return self; }

    inline constexpr degrees_t cast() const { return angle * pi; }
    inline constexpr operator degrees_t() const { return cast(); }
    inline constexpr operator angle_t<degrees_t>() const;

public:
    NULLSDK_ANGLE_IMPL_MAKE_FUNCTIONS(radians_t, sin);
    NULLSDK_ANGLE_IMPL_MAKE_FUNCTIONS(radians_t, cos);
    NULLSDK_ANGLE_IMPL_MAKE_FUNCTIONS(radians_t, tan);
};

template <>
struct angle_t<degrees_t> : public ntl::sdk::i_angle<degrees_t> {
public:
    static constexpr double pi = std::numbers::pi / 180.f;
    static constexpr degrees_t maximal_boundires = 360.f;
    static constexpr degrees_t minimal_boundires = maximal_boundires * -1.f;

public:
    static angle_t<degrees_t> atan2(const auto& y, const auto& x) { return angle_t<degrees_t>((radians_t)std::atan2(y, x)); }

public:
    inline constexpr angle_t() { }
    inline constexpr angle_t(degrees_t degrees) : i_angle(degrees) { }
    inline constexpr angle_t(radians_t radians);
    inline constexpr angle_t(const i_angle<degrees_t>& _angle) : i_angle(_angle) { }
    inline constexpr angle_t(const i_angle<radians_t>& radians);
    inline constexpr angle_t(const angle_t<radians_t>& radians);

public:
    template <degrees_t min = minimal_boundires, degrees_t max = maximal_boundires>
    angle_t<degrees_t> clamped() const { return std::clamp(angle, min, max); }

    template <degrees_t min = minimal_boundires, degrees_t max = maximal_boundires, typename self_t>
    auto&& clamp(this self_t&& self) { self = self.clamped<min, max>(); return self; }

    template <degrees_t min = minimal_boundires, degrees_t max = maximal_boundires>
    angle_t<degrees_t> normalized() const {
        static constexpr auto constexpr_abs = [](auto val) { return val < 0 ? -val : val; };
        constexpr auto boundaries = constexpr_abs(min - max);
        return degrees_t(angle - boundaries * std::floor((angle + (boundaries - max)) * (1. / boundaries)));
    }

    template <degrees_t min = minimal_boundires, degrees_t max = maximal_boundires, typename self_t>
    auto&& normalize(this self_t&& self) { self = self.normalized<min, max>(); return self; }

    inline constexpr radians_t cast() const { return angle * pi; }
    inline constexpr operator radians_t() const { return cast(); }
    inline constexpr operator angle_t<radians_t>() const;

public:
    NULLSDK_ANGLE_IMPL_MAKE_FUNCTIONS(degrees_t, sin);
    NULLSDK_ANGLE_IMPL_MAKE_FUNCTIONS(degrees_t, cos);
    NULLSDK_ANGLE_IMPL_MAKE_FUNCTIONS(degrees_t, tan);
};

inline constexpr angle_t<radians_t>::angle_t(const i_angle<degrees_t>& degrees) : angle_t(degrees.angle) { }
inline constexpr angle_t<radians_t>::angle_t(const angle_t<degrees_t>& degrees) : i_angle(degrees.cast()) { }
inline constexpr angle_t<radians_t>::angle_t(degrees_t degrees) : i_angle(degrees *angle_t<degrees_t>::pi) { }
inline constexpr angle_t<radians_t>::operator angle_t<degrees_t>() const { return angle_t<degrees_t>(cast()); }

inline constexpr angle_t<degrees_t>::angle_t(const i_angle<radians_t>& radians) : angle_t(radians.angle) { }
inline constexpr angle_t<degrees_t>::angle_t(const angle_t<radians_t>& radians) : i_angle(radians.cast()) { }
inline constexpr angle_t<degrees_t>::angle_t(radians_t radians) : i_angle(radians *angle_t<radians_t>::pi) { }
inline constexpr angle_t<degrees_t>::operator angle_t<radians_t>() const { return angle_t<radians_t>(cast()); }