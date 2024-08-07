#pragma once
#include <numbers>
#include <cmath>
#include <complex>
#include "../../utils/fast_operators.h"

using radians_t = double;
using degrees_t = float;

namespace null::literals {
    inline constexpr radians_t operator""rad(long double radians) { return radians; }
    inline constexpr degrees_t operator""deg(long double degrees) { return degrees; }
}

namespace null::sdk {
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

        fast_ops_structure_all_prefix_operators(inline constexpr, angle);
        fast_ops_structure_all_postfix_operators(inline constexpr, angle);

        fast_ops_structure_all_arithmetic_operators(inline constexpr, template <typename self_t>, const i_angle<value_t>&, rhs_field, angle);
        fast_ops_structure_all_arithmetic_operators(inline constexpr, template <typename self_t>, value_t, rhs_value, angle);

        inline constexpr auto operator<=>(const i_angle<value_t>&) const = default;
        inline constexpr auto operator<=>(value_t& other) const { return angle <=> other; }
    };
}

#define angle_impl_make_functions(return_t, name)	\
	return_t name() const;							\
	return_t a##name() const;						\
	return_t name##h() const;						\
	return_t a##name##h() const;					\

template <null::sdk::is_angle_type_t value_t>
struct angle_t { };

template <>
struct angle_t<radians_t> : public null::sdk::i_angle<radians_t> {
public:
    static constexpr double pi = 180. / std::numbers::pi;

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
    //@credits: https://stackoverflow.com/questions/2320986/easy-way-to-keeping-angles-between-179-and-180-degrees#comment52945562_2321125
    angle_t<radians_t> normalized() const { return std::log(std::exp(std::complex<double>(0., angle))).imag(); }
    template <typename self_t> auto&& normalize(this self_t&& self) { self = self.normalized(); return self; }

    inline constexpr degrees_t cast() const { return angle * pi; }
    inline constexpr operator degrees_t() const { return cast(); }
    inline constexpr operator angle_t<degrees_t>() const;

public:
    angle_impl_make_functions(radians_t, sin);
    angle_impl_make_functions(radians_t, cos);
    angle_impl_make_functions(radians_t, tan);
};

template <>
struct angle_t<degrees_t> : public null::sdk::i_angle<degrees_t> {
public:
    static constexpr double pi = std::numbers::pi / 180.f;

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
    angle_t<degrees_t> normalized() const { return std::log(std::exp(std::complex<double>(0., angle * pi))).imag() * angle_t<radians_t>::pi; }
    template <typename self_t> auto&& normalize(this self_t&& self) { self = self.normalized(); return self; }

    inline constexpr radians_t cast() const { return angle * pi; }
    inline constexpr operator radians_t() const { return cast(); }
    inline constexpr operator angle_t<radians_t>() const;

public:
    angle_impl_make_functions(degrees_t, sin);
    angle_impl_make_functions(degrees_t, cos);
    angle_impl_make_functions(degrees_t, tan);
};

inline constexpr angle_t<radians_t>::angle_t(const i_angle<degrees_t>& degrees) : angle_t(degrees.angle) { }
inline constexpr angle_t<radians_t>::angle_t(const angle_t<degrees_t>& degrees) : i_angle(degrees.cast()) { }
inline constexpr angle_t<radians_t>::angle_t(degrees_t degrees) : i_angle(degrees *angle_t<degrees_t>::pi) { }
inline constexpr angle_t<radians_t>::operator angle_t<degrees_t>() const { return angle_t<degrees_t>(cast()); }


inline constexpr angle_t<degrees_t>::angle_t(const i_angle<radians_t>& radians) : angle_t(radians.angle) { }
inline constexpr angle_t<degrees_t>::angle_t(const angle_t<radians_t>& radians) : i_angle(radians.cast()) { }
inline constexpr angle_t<degrees_t>::angle_t(radians_t radians) : i_angle(radians *angle_t<radians_t>::pi) { }
inline constexpr angle_t<degrees_t>::operator angle_t<radians_t>() const { return angle_t<radians_t>(cast()); }