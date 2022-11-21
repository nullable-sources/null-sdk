#pragma once
#include <array>
#include <stdexcept>
#include <algorithm>

#include <utils/fast_operators.h>

namespace null::sdk {
	template <typename channel_t>
	struct i_color {
	public:
		std::array<channel_t, 4> channels{ };

	public:
		i_color() { }

		i_color(channel_t _rgba) : i_color{ _rgba, _rgba, _rgba, _rgba } { };
		i_color(channel_t _r, channel_t _g, channel_t _b, channel_t _a) : channels{ _r, _g, _b, _a } { }

		i_color(const i_color<channel_t>& color, channel_t _a) : i_color{ color.r(), color.g(), color.b(), _a } { }

	public:
		channel_t& r() { return channels[0]; } const channel_t& r() const { return channels[0]; }
		channel_t& g() { return channels[1]; } const channel_t& g() const { return channels[1]; }
		channel_t& b() { return channels[2]; } const channel_t& b() const { return channels[2]; }
		channel_t& a() { return channels[3]; } const channel_t& a() const { return channels[3]; }

		template<typename cast_t>
		i_color<cast_t> cast() const { return i_color<cast_t>{ (cast_t)r(), (cast_t)g(), (cast_t)b(), (cast_t)a() }; }

	public:
		bool operator==(const i_color<channel_t>&) const = default;

		template <typename color_channel_t>
		i_color<channel_t> operator*(const i_color<color_channel_t>& color) const { return i_color<channel_t>{ r()* color.r(), g()* color.g(), b()* color.b(), a()* color.a() }; }
		template <typename color_channel_t>
		i_color<channel_t> operator*=(const i_color<color_channel_t>& color) { *this = *this * color; return *this; }

		template <typename color_channel_t>
		i_color<channel_t> operator/(const i_color<color_channel_t>& color) const { return i_color<channel_t>{ r() / color.r(), g() / color.g(), b() / color.b(), a() / color.a() }; }
		template <typename color_channel_t>
		i_color<channel_t> operator/=(const i_color<color_channel_t>& color) { *this = *this / color; return *this; }
	};
}

template <typename channels_t = int>
struct color_t : null::sdk::i_color<int> {
public: using i_color::i_color;
	struct palette_t {
		static inline const i_color<int> white	{ 255,	255,	255,	255 };
		static inline const i_color<int> black	{ 0,	0,		0,		255 };
		static inline const i_color<int> red	{ 255,	0,		0,		255 };
		static inline const i_color<int> green	{ 0,	255,	0,		255 };
		static inline const i_color<int> blue	{ 0,	0,		255,	255 };
	};

public:
	color_t() : i_color{ 255 } { }

	color_t(float _rgba) : i_color{ _rgba * 255 } { }
	color_t(int _r, int _g, int _b, int _a = 255) : i_color{ _r, _g, _b, _a } { }
	color_t(float _r, float _g, float _b, float _a = 1.f) : i_color{ color_t<float>{ _r, _g, _b, _a } } { }

	color_t(const i_color<int>& color) : i_color{ color } { }
	color_t(const i_color<int>& color, float _a) : i_color{ color, _a * 255 } { }
	color_t(const i_color<float>& color) : i_color{ color_t<float>{ color } } { }

public:
	operator i_color<float>() const { return this->cast<float>() / i_color<float>{ 255.f }; }
};

template <>
struct color_t<float> : null::sdk::i_color<float> {
public: using i_color::i_color;
	struct palette_t {
		static inline const i_color<float> white{ 1.f, 1.f, 1.f, 1.f };
		static inline const i_color<float> black{ 0.f, 0.f, 0.f, 1.f };
		static inline const i_color<float> red	{ 1.f, 0.f, 0.f, 1.f };
		static inline const i_color<float> green{ 0.f, 1.f, 0.f, 1.f };
		static inline const i_color<float> blue	{ 0.f, 0.f, 1.f, 1.f };
	};

public:
	color_t() : i_color{ 1.f } { }

	color_t(int _rgba) : i_color{ _rgba / 255.f } { }
	color_t(float _r, float _g, float _b, float _a = 1.f) : i_color{ _r, _g, _b, _a } { }
	color_t(int _r, int _g, int _b, int _a = 255) : i_color{ color_t<int>{ _r, _g, _b, _a } } { }

	color_t(const i_color<float>& color) : i_color{ color } { }
	color_t(const i_color<float>& color, int _a) : i_color{ color, _a / 255.f } { }
	color_t(const i_color<int>& color) : i_color{ color_t<int>{ color } } { }

public:
	operator i_color<int>() const { return i_color<float>{ *this * i_color<int>{ 255 } }.cast<int>(); }
};

struct hsv_color_t {
public:
	std::array<float, 4> channels{ };

public:
	hsv_color_t() : channels{ 0.f, 0.f, 1.f, 1.f } { }

	hsv_color_t(const null::sdk::i_color<float>& rgba) : channels{ rgba.channels } {
		float max{ std::ranges::max(rgba.channels | std::ranges::views::take(3)) };
		float delta{ max - std::ranges::min(rgba.channels | std::ranges::views::take(3)) };

		if(delta <= 0.f) channels = { 0.f, 0.f, max, rgba.a() };
		else {
			if(max == rgba.r())			h() = std::fmodf((rgba.g() - rgba.b()) / delta, 6.f);
			else if(max == rgba.g())	h() = (rgba.b() - rgba.r()) / delta + 2.f;
			else if(max == rgba.b())	h() = (rgba.r() - rgba.g()) / delta + 4.f;
			h() *= 60.f;
			if(h() < 0.f) h() += 360.f;

			s() = max > 0.f ? delta / max : 0.f;
			v() = max;
		}
	}

public:
	float& h() { return channels[0]; } const float& h() const { return channels[0]; }
	float& s() { return channels[1]; } const float& s() const { return channels[1]; }
	float& v() { return channels[2]; } const float& v() const { return channels[2]; }
	float& a() { return channels[3]; } const float& a() const { return channels[3]; }

public:
	operator null::sdk::i_color<float>() const {
		float chroma{ v() * s() };
		float prime{ std::fmod(h() / 60.f, 6.f) };
		float x{ chroma * (1.f - std::fabs(std::fmod(prime, 2.f) - 1.f)) };

		null::sdk::i_color<float> rgba{ };
		switch((int)prime) {
			case 0: rgba.r() = chroma;	rgba.g() = x;		rgba.b() = 0.f;		break;
			case 1: rgba.r() = x;		rgba.g() = chroma;	rgba.b() = 0.f;		break;
			case 2: rgba.r() = 0.f;		rgba.g() = chroma;	rgba.b() = x;		break;
			case 3: rgba.r() = 0.f;		rgba.g() = x;		rgba.b() = chroma;	break;
			case 4: rgba.r() = x;		rgba.g() = 0.f;		rgba.b() = chroma;	break;
			case 5: rgba.r() = chroma;	rgba.g() = 0.f;		rgba.b() = x;		break;
		}

		float m{ v() - chroma };
		return null::sdk::i_color<float>{ rgba.r() + m, rgba.g() + m, rgba.b() + m, a() };
	}
};