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
		i_color(channel_t _rgb, channel_t _a) : i_color{ _rgb, _rgb, _rgb, _a } { }
		i_color(channel_t _r, channel_t _g, channel_t _b, channel_t _a) : channels{ _r, _g, _b, _a } { }

		i_color(const i_color<channel_t>& color, channel_t _a) : i_color{ color.r(), color.g(), color.b(), _a } { }
		i_color(const std::vector<channel_t>& _channels) { std::ranges::copy(_channels, channels.begin()); }

	public:
		template <typename self_t> auto&& r(this self_t&& self) { return self.channels[0]; }
		template <typename self_t> auto&& g(this self_t&& self) { return self.channels[1]; }
		template <typename self_t> auto&& b(this self_t&& self) { return self.channels[2]; }
		template <typename self_t> auto&& a(this self_t&& self) { return self.channels[3]; }

		template<typename cast_t>
		i_color<cast_t> cast() const { return i_color<cast_t>{ channels | std::views::transform([](const channel_t& channel) { return (cast_t)channel; }) | std::ranges::to<std::vector>() }; }

	public:
		//@note: i hope i will live to see the moment when they add support https://en.cppreference.com/w/cpp/ranges/zip_view
		class_create_operators(i_color<channel_t>, -, { return i_color<channel_t>(-r(), -g(), -b(), -a()); }, ());
		impl_class_create_arithmetic_operators(color, i_color<channel_t>, i_color<other_channel_t>, +, { return i_color<channel_t>(r() + color.r(), g() + color.g(), b() + color.b(), a() + color.a()); }, impl_default_arithmetic_assignment_func(+, color), template <typename other_channel_t>);
		impl_class_create_arithmetic_operators(color, i_color<channel_t>, i_color<other_channel_t>, -, { return i_color<channel_t>(r() - color.r(), g() - color.g(), b() - color.b(), a() - color.a()); }, impl_default_arithmetic_assignment_func(-, color), template <typename other_channel_t>);
		impl_class_create_arithmetic_operators(color, i_color<channel_t>, i_color<other_channel_t>, *, { return i_color<channel_t>(r() * color.r(), g() * color.g(), b() * color.b(), a() * color.a()); }, impl_default_arithmetic_assignment_func(*, color), template <typename other_channel_t>);
		impl_class_create_arithmetic_operators(color, i_color<channel_t>, i_color<other_channel_t>, /, { return i_color<channel_t>(r() / color.r(), g() / color.g(), b() / color.b(), a() / color.a()); }, impl_default_arithmetic_assignment_func(/, color), template <typename other_channel_t>);

		bool operator==(const i_color<channel_t>&) const = default;
		class_create_logic_operators(color, i_color<channel_t>, <, { return r() < color.r() && g() < color.g() && b() < color.b() && a() < color.a(); }, { return r() <= color.r() && g() <= color.g() && b() <= color.b() && a() <= color.a(); });
		class_create_logic_operators(color, i_color<channel_t>, >, { return r() > color.r() && g() > color.g() && b() > color.b() && a() > color.a(); }, { return r() >= color.r() && g() >= color.g() && b() >= color.b() && a() >= color.a(); });
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
	
	color_t(int	_rgb, float	_a) : i_color{ _rgb, _a * 255 } { }
	color_t(float _rgb, int	_a) : i_color{ _rgb * 255, _a } { }
	color_t(float _rgb, float _a) : i_color{ _rgb * 255, _a * 255 } { }
	
	color_t(int _r, int _g, int _b, int _a = 255) : i_color{ _r, _g, _b, _a } { }
	color_t(float _r, float _g, float _b, float _a = 1.f) : i_color{ color_t<float>{ _r, _g, _b, _a } } { }

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

	color_t(int _rgba) : i_color{ _rgba / 255.f } { }

	color_t(float _rgb, int	_a) : i_color{ _rgb, _a / 255.f } { }
	color_t(int _rgb, float _a) : i_color{ _rgb / 255.f, _a } { }
	color_t(int _rgb, int _a) : i_color{ _rgb / 255.f, _a / 255.f } { }
	
	color_t(float _r, float _g, float _b, float _a = 1.f) : i_color{ _r, _g, _b, _a } { }
	color_t(int _r, int _g, int _b, int _a = 255) : i_color{ color_t<int>{ _r, _g, _b, _a } } { }

	color_t(const i_color<float>& color) : i_color{ color } { }
	color_t(const i_color<float>& color, int _a) : i_color{ color, _a / 255.f } { }
	color_t(const i_color<int>& color) : i_color{ color_t<int>{ color } } { }

private:
	color_t<float> round() { std::ranges::transform(channels, channels.begin(), [](const float& channel) { return std::round(channel); }); return *this; }

public:
	operator i_color<int>() const { return color_t<float>{ *this * color_t<int>{ 255 } }.round().cast<int>(); }
};

struct hsv_color_t {
public:
	std::array<float, 4> channels{ };

public:
	hsv_color_t() : channels{ 0.f, 0.f, 1.f, 1.f } { }
	hsv_color_t(float _h, float _a = 1.f) : hsv_color_t{ _h, 1.f, 1.f, _a } { }
	hsv_color_t(float _h, float _s, float _v, float _a = 1.f) : channels{ _h, _s, _v, _a } { }
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

	class_create_operators(hsv_color_t, -, { return hsv_color_t(-h(), -s(), -v(), -a()); }, ());
	class_create_arithmetic_operators(color, hsv_color_t, +, { return hsv_color_t(h() + color.h(), s() + color.s(), v() + color.v(), a() + color.a()); });
	class_create_arithmetic_operators(color, hsv_color_t, -, { return hsv_color_t(h() - color.h(), s() - color.s(), v() - color.v(), a() - color.a()); });
	class_create_arithmetic_operators(color, hsv_color_t, *, { return hsv_color_t(h() * color.h(), s() * color.s(), v() * color.v(), a() * color.a()); });
	class_create_arithmetic_operators(color, hsv_color_t, /, { return hsv_color_t(h() / color.h(), s() / color.s(), v() / color.v(), a() / color.a()); });
	
	bool operator==(const hsv_color_t&) const = default;
	class_create_logic_operators(color, hsv_color_t, <, { return h() < color.h() && s() < color.s() && v() < color.v() && a() < color.a(); }, { return h() <= color.h() && s() <= color.s() && v() <= color.v() && a() <= color.a(); });
	class_create_logic_operators(color, hsv_color_t, >, { return h() > color.h() && s() > color.s() && v() > color.v() && a() > color.a(); }, { return h() >= color.h() && s() >= color.s() && v() >= color.v() && a() >= color.a(); });
};