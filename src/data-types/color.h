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

		i_color(const channel_t& _rgba) : i_color{ _rgba, _rgba, _rgba, _rgba } { };
		i_color(const channel_t& _rgb, const channel_t& _a) : i_color{ _rgb, _rgb, _rgb, _a } { }
		i_color(const channel_t& _r, const channel_t& _g, const channel_t& _b, const channel_t& _a) : channels{ _r, _g, _b, _a } { }

		i_color(const i_color<channel_t>& color, const channel_t& _a) : i_color{ color.r(), color.g(), color.b(), _a } { }
		i_color(const std::vector<channel_t>& _channels) { std::ranges::move(_channels, channels.begin()); }

	public:
		template <typename self_t> auto&& r(this self_t&& self) { return self.channels[0]; }
		template <typename self_t> auto&& g(this self_t&& self) { return self.channels[1]; }
		template <typename self_t> auto&& b(this self_t&& self) { return self.channels[2]; }
		template <typename self_t> auto&& a(this self_t&& self) { return self.channels[3]; }

		template<typename cast_t>
		i_color<cast_t> cast() const { return i_color<cast_t>{ channels | std::views::transform([](const channel_t& channel) { return (cast_t)channel; }) | std::ranges::to<std::vector>() }; }

	public:	
		template <typename self_t> auto operator -(this self_t&& self) { return i_color{ -self.r(), -self.g(), -self.b(), -self.a() }; }
		class_create_arithmetic_operators(color, i_color, -, { return i_color(self.r() - color.r(), self.g() - color.g(), self.b() - color.b(), self.a() - color.a()); });
		class_create_arithmetic_operators(color, i_color, +, { return i_color(self.r() + color.r(), self.g() + color.g(), self.b() + color.b(), self.a() + color.a()); });
		class_create_arithmetic_operators(color, i_color, *, { return i_color(self.r() * color.r(), self.g() * color.g(), self.b() * color.b(), self.a() * color.a()); });
		class_create_arithmetic_operators(color, i_color, /, { return i_color(self.r() / color.r(), self.g() / color.g(), self.b() / color.b(), self.a() / color.a()); });
		class_create_arithmetic_operators(color, i_color, %, { return i_color(self.r() % color.r(), self.g() % color.g(), self.b() % color.b(), self.a() % color.a()); });

		template <typename another_channel_t> bool operator==(const i_color<another_channel_t>& color) const { return channels == color.channels; };
		class_create_logic_operators(color, i_color, <, { return self.r() < color.r() && self.g() < color.g() && self.b() < color.b() && self.a() < color.a(); }, { return self.r() <= color.r() && self.g() <= color.g() && self.b() <= color.b() && self.a() <= color.a(); });
		class_create_logic_operators(color, i_color, >, { return self.r() > color.r() && self.g() > color.g() && self.b() > color.b() && self.a() > color.a(); }, { return self.r() >= color.r() && self.g() >= color.g() && self.b() >= color.b() && self.a() >= color.a(); });
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

	color_t(const float& _rgba) : i_color{ _rgba * 255 } { }
	
	color_t(const int& _rgb, const float& _a) : i_color{ _rgb, _a * 255 } { }
	color_t(const float& _rgb, const int& _a) : i_color{ _rgb * 255, _a } { }
	color_t(const float& _rgb, const float& _a) : i_color{ _rgb * 255, _a * 255 } { }
	
	color_t(const int& _r, const int& _g, const int& _b, const int& _a = 255) : i_color{ _r, _g, _b, _a } { }
	color_t(const float& _r, const float& _g, const float& _b, const float& _a = 1.f) : i_color{ color_t<float>{ _r, _g, _b, _a } } { }

	color_t(const i_color<int>& color) : i_color{ color } { }
	color_t(const i_color<int>& color, float _a) : i_color{ color, _a * 255 } { }
	color_t(const i_color<float>& color) : i_color{ color_t<float>{ color } } { }

public:
	operator i_color<float>() const { return this->cast<float>() / color_t<float>{ 255.f }; }
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

	color_t(const int& _rgba) : i_color{ _rgba / 255.f } { }

	color_t(const float& _rgb, const int& _a) : i_color{ _rgb, _a / 255.f } { }
	color_t(const int& _rgb, const float& _a) : i_color{ _rgb / 255.f, _a } { }
	color_t(const int& _rgb, const int& _a) : i_color{ _rgb / 255.f, _a / 255.f } { }
	
	color_t(const float& _r, const float& _g, const float& _b, const float& _a = 1.f) : i_color{ _r, _g, _b, _a } { }
	color_t(const int& _r, const int& _g, const int& _b, const int& _a = 255) : i_color{ color_t<int>{ _r, _g, _b, _a } } { }

	color_t(const i_color<float>& color) : i_color{ color } { }
	color_t(const i_color<float>& color, int _a) : i_color{ color, _a / 255.f } { }
	color_t(const i_color<int>& color) : i_color{ color_t<int>{ color } } { }

private:
	color_t<float>& round() { std::ranges::transform(channels, channels.begin(), [](const float& channel) { return std::round(channel); }); return *this; }

public:
	operator i_color<int>() const { return color_t<float>{ *this * color_t<float>{ 255.f } }.round().cast<int>(); }
};

struct hsv_color_t {
public:
	std::array<float, 4> channels{ };

public:
	hsv_color_t() : channels{ 0.f, 0.f, 1.f, 1.f } { }
	hsv_color_t(const float& _h, const float& _a = 1.f) : hsv_color_t{ _h, 1.f, 1.f, _a } { }
	hsv_color_t(const float& _h, const float& _s, const float& _v, const float& _a = 1.f) : channels{ _h, _s, _v, _a } { }
	hsv_color_t(const null::sdk::i_color<float>& rgba) : channels{ rgba.channels } {
		double max{ std::ranges::max(rgba.channels | std::views::take(3)) };
		double delta{ max - std::ranges::min(rgba.channels | std::views::take(3)) };

		if(delta <= 0.f) channels = { 0.f, 0.f, (float)max, rgba.a() };
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
	template <typename self_t> auto&& h(this self_t&& self) { return self.channels[0]; }
	template <typename self_t> auto&& s(this self_t&& self) { return self.channels[1]; }
	template <typename self_t> auto&& v(this self_t&& self) { return self.channels[2]; }
	template <typename self_t> auto&& a(this self_t&& self) { return self.channels[3]; }

public:
	operator null::sdk::i_color<float>() const {
		double chroma{ v() * s() };
		double prime{ std::fmod(h() / 60.f, 6.f) };
		double x{ chroma * (1.f - std::fabs(std::fmod(prime, 2.f) - 1.f)) };

		null::sdk::i_color<float> rgba{ };
		switch((int)prime) {
			case 0: rgba.r() = chroma;	rgba.g() = x;		rgba.b() = 0.f;		break;
			case 1: rgba.r() = x;		rgba.g() = chroma;	rgba.b() = 0.f;		break;
			case 2: rgba.r() = 0.f;		rgba.g() = chroma;	rgba.b() = x;		break;
			case 3: rgba.r() = 0.f;		rgba.g() = x;		rgba.b() = chroma;	break;
			case 4: rgba.r() = x;		rgba.g() = 0.f;		rgba.b() = chroma;	break;
			case 5: rgba.r() = chroma;	rgba.g() = 0.f;		rgba.b() = x;		break;
		}

		double m{ v() - chroma };
		return null::sdk::i_color<double>{ rgba.r() + m, rgba.g() + m, rgba.b() + m, a() }.cast<float>();
	}

	template <typename self_t> auto operator -(this self_t&& self) { return hsv_color_t{ -self.h(), -self.s(), -self.v(), -self.a() }; }
	class_create_arithmetic_operators(color, hsv_color_t, +, { return hsv_color_t(self.h() + color.h(), self.s() + color.s(), self.v() + color.v(), self.a() + color.a()); });
	class_create_arithmetic_operators(color, hsv_color_t, -, { return hsv_color_t(self.h() - color.h(), self.s() - color.s(), self.v() - color.v(), self.a() - color.a()); });
	class_create_arithmetic_operators(color, hsv_color_t, *, { return hsv_color_t(self.h() * color.h(), self.s() * color.s(), self.v() * color.v(), self.a() * color.a()); });
	class_create_arithmetic_operators(color, hsv_color_t, /, { return hsv_color_t(self.h() / color.h(), self.s() / color.s(), self.v() / color.v(), self.a() / color.a()); });
	
	bool operator==(const hsv_color_t&) const = default;
	class_create_logic_operators(color, hsv_color_t, <, { return self.h() < color.h() && self.s() < color.s() && self.v() < color.v() && self.a() < color.a(); }, { return self.h() <= color.h() && self.s() <= color.s() && self.v() <= color.v() && self.a() <= color.a(); });
	class_create_logic_operators(color, hsv_color_t, >, { return self.h() > color.h() && self.s() > color.s() && self.v() > color.v() && self.a() > color.a(); }, { return self.h() >= color.h() && self.s() >= color.s() && self.v() >= color.v() && self.a() >= color.a(); });
};