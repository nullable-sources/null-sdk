#pragma once
#include <numbers>
#include <cmath>

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
    template <typename self_t> auto&& normalize(this self_t&& self) { self.value = std::numbers::pi - std::remainder(std::abs(self.value), std::numbers::pi); return self; }

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
    template <typename self_t> auto&& normalize(this self_t&& self) { self.value = 180.f - std::remainder(std::abs(self.value), 180.f); return self; }

    radians_t cast() const;
    operator radians_t() const;
    operator angle_t<radians_t>() const;
};