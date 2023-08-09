#pragma once
#include <numbers>
#include <cmath>
#include <complex>
#include "utils/fast_operators.h"

using radians_t = double;
using degrees_t = float;

namespace null::sdk::impl {
    template <typename value_t>
    class i_angle {
    public:
        value_t value{ };

    public:
        i_angle() { }
        i_angle(value_t _value) : value{ _value } { }

    public:
        operator value_t(this auto&& self) { return self.value; }

#define fast_arithmetic_operators(op)                                                                                                                                               \
    impl_class_create_operator(auto, op, { return i_angle<value_t>(self.value op angle.value); }, (this self_t&& self, const i_angle<value_t>& angle), template <typename self_t>)  \
    impl_class_create_operator(value_t, op, { return self.value op angle; }, (this self_t&& self, const value_t& angle), template <typename self_t>)                                \
    impl_class_create_operator(auto&&, op##=, impl_default_arithmetic_assignment_func(op, angle), (this self_t&& self, const i_angle<value_t>& angle), template <typename self_t>)  \
    impl_class_create_operator(auto&&, op##=, impl_default_arithmetic_assignment_func(op, angle), (this self_t&& self, const value_t& angle), template <typename self_t>)           \

        fast_arithmetic_operators(-); fast_arithmetic_operators(+); fast_arithmetic_operators(*); fast_arithmetic_operators(/ ); fast_arithmetic_operators(%);

#define fast_logic_operators(op)                                                                                                                \
    class_create_logic_operators_default(angle, i_angle<value_t>, op, { return self.value op angle.value; }, { return self.value op##= angle.value; }); \
    class_create_logic_operators_default(angle, value_t, op, { return self.value op angle; }, { return self.value op##= angle; });                      \

        fast_logic_operators(< ); fast_logic_operators(> );

        bool operator ==(value_t angle) const { return value == angle; };
    };
}

template <typename value_t>
struct angle_t { };

#define angle_impl_make_functions(return_t, name)   \
    return_t name() const;                          \
    return_t a##name() const;                       \
    return_t name##h() const;                       \
    return_t a##name##h() const;                    \

template <>
struct angle_t<radians_t> : public null::sdk::impl::i_angle<radians_t> {
public:
    static constexpr double pi{ 180. / std::numbers::pi };

public:
    static angle_t<radians_t> atan2(auto y, auto x) { return angle_t<radians_t>{ (radians_t)std::atan2(y, x) }; }

public:
    angle_t() { }
    angle_t(radians_t radians) : i_angle{ radians } { }
    angle_t(degrees_t degrees);
    angle_t(const i_angle<radians_t>& angle) : i_angle{ angle } { }
    angle_t(const i_angle<degrees_t>& degrees);
    angle_t(const angle_t<degrees_t>& degrees);

public:
    //@credits: https://stackoverflow.com/questions/2320986/easy-way-to-keeping-angles-between-179-and-180-degrees#comment52945562_2321125
    angle_t<radians_t> normalized(this auto&& self) { return std::log(std::exp(std::complex<double>{ 0., self.value })).imag(); }
    auto&& normalize(this auto&& self) { self = self.normalized(); return self; }

    degrees_t cast() const;
    operator degrees_t() const;
    operator angle_t<degrees_t>() const;

public:
    angle_impl_make_functions(radians_t, sin);
    angle_impl_make_functions(radians_t, cos);
    angle_impl_make_functions(radians_t, tan);
};

template <>
struct angle_t<degrees_t> : public null::sdk::impl::i_angle<degrees_t> {
public:
    static constexpr double pi{ std::numbers::pi / 180.f };

public:
    static angle_t<degrees_t> atan2(const auto& y, const auto& x) { return angle_t<degrees_t>{ (radians_t)std::atan2(y, x) }; }

public:
    angle_t() { }
    angle_t(degrees_t degrees) : i_angle{ degrees } { }
    angle_t(radians_t radians);
    angle_t(const i_angle<degrees_t>& angle) : i_angle{ angle } { }
    angle_t(const i_angle<radians_t>& radians);
    angle_t(const angle_t<radians_t>& radians);

public:
    angle_t<degrees_t> normalized(this auto&& self) { return std::log(std::exp(std::complex<double>{ 0., self.value * pi })).imag() * angle_t<radians_t>::pi; }
    auto&& normalize(this auto&& self) { self = self.normalized(); return self; }

    radians_t cast() const;
    operator radians_t() const;
    operator angle_t<radians_t>() const;

public:
    angle_impl_make_functions(degrees_t, sin);
    angle_impl_make_functions(degrees_t, cos);
    angle_impl_make_functions(degrees_t, tan);
};