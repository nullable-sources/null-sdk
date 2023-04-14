#pragma once
#include <numbers>
#include <cmath>
#include <complex>
#include <utils/fast_operators.h>

using radians_t = double;
using degrees_t = float;

namespace null::sdk::impl {
    template <typename value_t>
    class i_angle {
    public:
        value_t value{ };

    public:
        i_angle() { }
        i_angle(const value_t& _value) : value{ _value } { }

    public:
        template <typename self_t> operator value_t(this self_t&& self) { return self.value; }

#define fast_arithmetic_operators(op)                                                                                                                                               \
    impl_class_create_operator(auto, op, { return i_angle<value_t>(self.value op angle.value); }, (this self_t&& self, const i_angle<value_t>& angle), template <typename self_t>)  \
    impl_class_create_operator(value_t, op, { return self.value op angle; }, (this self_t&& self, const value_t& angle), template <typename self_t>)                                \
    impl_class_create_operator(auto&&, op##=, impl_default_arithmetic_assignment_func(op, angle), (this self_t&& self, const i_angle<value_t>& angle), template <typename self_t>)  \
    impl_class_create_operator(auto&&, op##=, impl_default_arithmetic_assignment_func(op, angle), (this self_t&& self, const value_t& angle), template <typename self_t>)           \

        fast_arithmetic_operators(-); fast_arithmetic_operators(+); fast_arithmetic_operators(*); fast_arithmetic_operators(/ ); fast_arithmetic_operators(%);

#define fast_logic_operators(op)                                                                                                                \
    class_create_logic_operators(angle, i_angle<value_t>, op, { return self.value op angle.value; }, { return self.value op##= angle.value; }); \
    class_create_logic_operators(angle, value_t, op, { return self.value op angle; }, { return self.value op##= angle; });                      \

        fast_logic_operators(< ); fast_logic_operators(> );

        bool operator ==(const value_t& angle) const { return value == angle; };
    };
}

template <typename value_t>
struct angle_t { };

template <>
struct angle_t<radians_t> : public null::sdk::impl::i_angle<radians_t> {
public:
    static constexpr double pi{ 180. / std::numbers::pi };

public:
    angle_t() { }
    angle_t(const radians_t& radians) : i_angle{ radians } { }
    angle_t(const degrees_t& degrees);
    angle_t(const angle_t<degrees_t>& degrees);

public:
    //@credits: https://stackoverflow.com/questions/2320986/easy-way-to-keeping-angles-between-179-and-180-degrees#comment52945562_2321125
    template <typename self_t> angle_t<radians_t> normalized(this self_t&& self) { return std::log(std::exp(std::complex<double>{ 0., self.value })).imag(); }
    template <typename self_t> auto&& normalize(this self_t&& self) { self = self.normalized(); return self; }

    degrees_t cast() const;
    operator degrees_t() const;
    operator angle_t<degrees_t>() const;
};

template <>
struct angle_t<degrees_t> : public null::sdk::impl::i_angle<degrees_t> {
public:
    static constexpr double pi{ std::numbers::pi / 180.f };

public:
    angle_t() { }
    angle_t(const degrees_t& degrees) : i_angle{ degrees } { }
    angle_t(const radians_t& radians);
    angle_t(const angle_t<radians_t>& radians_t);

public:
    template <typename self_t> angle_t<degrees_t> normalized(this self_t&& self) { return std::log(std::exp(std::complex<double>{ 0., self.value * pi })).imag() * angle_t<radians_t>::pi; }
    template <typename self_t> auto&& normalize(this self_t&& self) { self = self.normalized(); return self; }

    radians_t cast() const;
    operator radians_t() const;
    operator angle_t<radians_t>() const;
};