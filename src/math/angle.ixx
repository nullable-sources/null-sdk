module;
#include <numbers>
#include <cmath>
#include <complex>

#include <utils/fast_operators.h>
export module null.sdk:math.angle;

export using radians_t = double;
export using degrees_t = float;

export namespace null::sdk::impl {
    template <typename value_t>
    class i_angle {
    public:
        value_t value{ };

    public:
        i_angle() { }
        i_angle(value_t _value) : value{ _value } { }

    public:
        operator value_t() const { return value; }

#define fast_arithmetic_operators(op)                                                                                               \
    impl_class_create_operator(auto, op, { return i_angle<value_t>(value op angle.value); }, (const i_angle<value_t>& angle) const) \
    impl_class_create_operator(value_t, op, { return value op angle; }, (const value_t& angle) const)                               \
    impl_class_create_operator(auto&, op##=, impl_default_arithmetic_assignment_func(op, angle), (const i_angle<value_t>& angle))   \
    impl_class_create_operator(auto&, op##=, impl_default_arithmetic_assignment_func(op, angle), (const value_t& angle))            \

        fast_arithmetic_operators(-); fast_arithmetic_operators(+); fast_arithmetic_operators(*); fast_arithmetic_operators(/ ); fast_arithmetic_operators(%);

#define fast_logic_operators(op)                                                                                                        \
    class_create_logic_operators(angle, i_angle<value_t>, op, { return value op angle.value; }, { return value op##= angle.value; });   \
    class_create_logic_operators(angle, value_t, op, { return value op angle; }, { return value op##= angle; });                        \

        fast_logic_operators(< ); fast_logic_operators(> );

        bool operator ==(const value_t& angle) const { return value == angle; };
    };
}

export template <typename value_t>
struct angle_t { };

#define make_functions_declaration(return_t, name)  \
    return_t name() const;                          \
    return_t a##name() const;                       \
    return_t name##h() const;                       \
    return_t a##name##h() const;                    \

export template <>
struct angle_t<radians_t> : public null::sdk::impl::i_angle<radians_t> {
public:
    static constexpr double pi{ 180. / std::numbers::pi };

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
    angle_t<radians_t> normalized() const { return std::log(std::exp(std::complex<double>{ 0., value })).imag(); }
    auto& normalize() { *this = normalized(); return *this; }

    degrees_t cast() const;
    operator degrees_t() const;
    operator angle_t<degrees_t>() const;

public:
    make_functions_declaration(radians_t, sin);
    make_functions_declaration(radians_t, cos);
    make_functions_declaration(radians_t, tan);
};

export template <>
struct angle_t<degrees_t> : public null::sdk::impl::i_angle<degrees_t> {
public:
    static constexpr double pi{ std::numbers::pi / 180.f };

    static angle_t<degrees_t> atan2(auto y, auto x) { return angle_t<degrees_t>{ (radians_t)std::atan2(y, x) }; }

public:
    angle_t() { }
    angle_t(degrees_t degrees) : i_angle{ degrees } { }
    angle_t(radians_t radians);
    angle_t(const i_angle<degrees_t>& angle) : i_angle{ angle } { }
    angle_t(const i_angle<radians_t>& radians);
    angle_t(const angle_t<radians_t>& radians);

public:
    angle_t<degrees_t> normalized() const { return std::log(std::exp(std::complex<double>{ 0., value * pi })).imag() * angle_t<radians_t>::pi; }
    auto& normalize() { *this = normalized(); return *this; }

    radians_t cast() const;
    operator radians_t() const;
    operator angle_t<radians_t>() const;

public:
    make_functions_declaration(degrees_t, sin);
    make_functions_declaration(degrees_t, cos);
    make_functions_declaration(degrees_t, tan);
};

angle_t<radians_t>::angle_t(const i_angle<degrees_t>& degrees) : angle_t{ degrees.value } { }
angle_t<radians_t>::angle_t(const angle_t<degrees_t>& degrees) : i_angle{ degrees.cast() } { }
angle_t<radians_t>::angle_t(degrees_t degrees) : i_angle{ degrees * angle_t<degrees_t>::pi } { }

degrees_t angle_t<radians_t>::cast() const { return value * pi; }
angle_t<radians_t>::operator degrees_t() const { return cast(); }
angle_t<radians_t>::operator angle_t<degrees_t>() const { return angle_t<degrees_t>{ cast() }; }


angle_t<degrees_t>::angle_t(const i_angle<radians_t>& radians) : angle_t{ radians.value } { }
angle_t<degrees_t>::angle_t(const angle_t<radians_t>& radians) : i_angle{ radians.cast() } { }
angle_t<degrees_t>::angle_t(radians_t radians) : i_angle{ (degrees_t)(radians * angle_t<radians_t>::pi) } { }

radians_t angle_t<degrees_t>::cast() const { return value * pi; }
angle_t<degrees_t>::operator radians_t() const { return cast(); }
angle_t<degrees_t>::operator angle_t<radians_t>() const { return angle_t<radians_t>{ cast() }; }

#define make_function_definition(type, name, body) type angle_t<type>::name##() const { return body; }

#define degrees_function_definition(name) make_function_definition(degrees_t, name, std::name##(cast()) * angle_t<radians_t>::pi)
#define radians_function_definition(name) make_function_definition(radians_t, name, std::name##(value))

#define make_functions_definition(type, name) type(name) type(a##name) type(name##h) type(a##name##h)	

make_functions_definition(degrees_function_definition, sin);
make_functions_definition(degrees_function_definition, cos);
make_functions_definition(degrees_function_definition, tan);

make_functions_definition(radians_function_definition, sin);
make_functions_definition(radians_function_definition, cos);
make_functions_definition(radians_function_definition, tan);