#pragma once
#include <array>
#include <ranges>
#include <algorithm>

#include "utils/fast_operators.h"
#include "data-types/vec4.h"

namespace null::sdk {
	template <typename channel_t>
	struct i_color {
	public:
		static constexpr size_t channels_size{ 4 }; //@note: size array{ r, g, b, a }

	public:
		union {
			struct { channel_t r, g, b, a; };
			std::array<channel_t, channels_size> channels{ };
		};

	public:
		i_color() { }

		i_color(channel_t _rgba) : i_color{ _rgba, _rgba, _rgba, _rgba } { };
		i_color(channel_t _rgb, channel_t _a) : i_color{ _rgb, _rgb, _rgb, _a } { }
		i_color(channel_t _r, channel_t _g, channel_t _b, channel_t _a) : channels{ _r, _g, _b, _a } { }

		i_color(const vec3_t<channel_t> _rgb, channel_t _a) : i_color{ _rgb.x, _rgb.y, _rgb.z, _a } { }
		i_color(const vec4_t<channel_t> _rgba) : i_color{ _rgba.x, _rgba.y, _rgba.z, _rgba.w } { }

		i_color(const i_color<channel_t>& color, channel_t _a) : i_color{ color.r, color.g, color.b, _a } { }
		i_color(const std::array<channel_t, channels_size>& _channels) : channels{ _channels } { }
		i_color(const std::vector<channel_t>& _channels) { std::move(_channels.begin(), std::next(_channels.begin(), std::min(_channels.size(), channels_size)), channels.begin()); }

		template <typename type_t> requires null::compatibility::data_type_convertertable<type_t, i_color<channel_t>>
		i_color(const type_t& value) : i_color{ null::compatibility::data_type_converter_t<type_t, i_color<channel_t>>::convert(value) } { }

	public:
		template <typename other_t> i_color<other_t> cast() const { return i_color<other_t>{ (other_t)r, (other_t)g, (other_t)b, (other_t)a }; }

		template <typename self_t> auto rgb(this self_t&& self) { return vec3_t<channel_t>{ self.r, self.g, self.b }; }

	public:
		fast_ops_structure_convert_operator(, vec3_t<channel_t>() const, vec3_t<channel_t>, , r, g, b);
		fast_ops_structure_convert_operator(, vec4_t<channel_t>() const, vec4_t<channel_t>, , r, g, b, a);
		fast_ops_structure_convert_operator(, fast_ops_args_pack(std::tuple<channel_t, channel_t, channel_t, channel_t>)() const, std::make_tuple, , r, g, b, a);

		template <typename type_t> requires null::compatibility::data_type_convertertable<i_color<channel_t>, type_t>
		operator type_t() const { return null::compatibility::data_type_converter_t<i_color<channel_t>, type_t>::convert(*this); }

		fast_ops_structure_all_prefix_operators(r, g, b, a);
		fast_ops_structure_all_postfix_operators(r, g, b, a);

		fast_ops_structure_all_arithmetic_operators(fast_ops_args_pack(template <typename self_t, typename other_t>), const i_color<other_t>&, rhs_field, r, g, b, a);
		fast_ops_structure_all_arithmetic_operators(template <typename self_t>, channel_t, rhs_value, r, g, b, a);

		fast_ops_structure_equal_operator(template <typename other_t>, const i_color<other_t>&, rhs_field, r, g, b, a);
		fast_ops_structure_equal_operator(, channel_t, rhs_value, r, g, b, a);

		fast_ops_structure_all_comparison_operators(fast_ops_args_pack(template <typename self_t, typename other_t>), const i_color<other_t>&, rhs_field, r, g, b, a);
		fast_ops_structure_all_comparison_operators(template <typename self_t>, channel_t, rhs_value, r, g, b, a);
	};
}

template <typename channel_t>
struct color_t { };

template <>
struct color_t<int> : public null::sdk::i_color<int> {
public:
	struct palette_t {
	public:
		static inline const i_color<int> white	{ 255,	255,	255,	255 };
		static inline const i_color<int> black	{ 0,	0,		0,		255 };
		static inline const i_color<int> red	{ 255,	0,		0,		255 };
		static inline const i_color<int> green	{ 0,	255,	0,		255 };
		static inline const i_color<int> blue	{ 0,	0,		255,	255 };
	};

public:
	using i_color::i_color;
	color_t() : i_color{ 255 } { }

	color_t(float _rgba) : i_color{ (int)(_rgba * 255.f) } { }
	
	color_t(int _rgb, float _a) : i_color{ _rgb, (int)(_a * 255.f) } { }
	color_t(float _rgb, int _a) : i_color{ (int)(_rgb * 255.f), _a } { }
	color_t(float _rgb, float _a) : i_color{ (int)(_rgb * 255.f), (int)(_a * 255.f) } { }
	
	color_t(int _r, int _g, int _b, int _a = 255) : i_color{ _r, _g, _b, _a } { }
	color_t(float _r, float _g, float _b, float _a = 1.f);

	color_t(const i_color<int>& color) : i_color{ color } { }
	color_t(const i_color<int>& color, float _a) : i_color{ color, (int)(_a * 255.f) } { }
	color_t(const i_color<float>& color);

public:
	operator i_color<float>() const { return cast<float>() / 255.f; }
};

template <>
struct color_t<float> : null::sdk::i_color<float> {
public:
	struct palette_t {
	public:
		static inline const i_color<float> white{ 1.f, 1.f, 1.f, 1.f };
		static inline const i_color<float> black{ 0.f, 0.f, 0.f, 1.f };
		static inline const i_color<float> red	{ 1.f, 0.f, 0.f, 1.f };
		static inline const i_color<float> green{ 0.f, 1.f, 0.f, 1.f };
		static inline const i_color<float> blue	{ 0.f, 0.f, 1.f, 1.f };
	};

public:
	using i_color::i_color;
	color_t() : i_color{ 1.f } { }

	color_t(int _rgba) : i_color{ (float)_rgba / 255.f } { }

	color_t(float _rgb, int _a) : i_color{ _rgb, (float)_a / 255.f } { }
	color_t(int _rgb, float _a) : i_color{ (float)_rgb / 255.f, _a } { }
	color_t(int _rgb, int _a) : i_color{ (float)_rgb / 255.f, (float)_a / 255.f } { }
	
	color_t(float _r, float _g, float _b, float _a = 1.f) : i_color{ _r, _g, _b, _a } { }
	color_t(int _r, int _g, int _b, int _a = 255);

	color_t(const i_color<float>& color) : i_color{ color } { }
	color_t(const i_color<float>& color, int _a) : i_color{ color, _a / 255.f } { }
	color_t(const i_color<int>& color);

private:
	template <typename self_t> auto&& round(this self_t&& self) { std::ranges::transform(self.channels, self.channels.begin(), std::roundf); return self; }

public:
	operator i_color<int>() const { return color_t<float>{ *this * 255 }.round().cast<int>(); }
};

struct hsv_color_t {
public:
	union {
		struct { float h, s, v, a; };
		std::array<float, 4> channels{ };
	};

public:
	hsv_color_t() : channels{ 0.f, 0.f, 1.f, 1.f } { }
	hsv_color_t(float _h, float _a = 1.f) : hsv_color_t{ _h, 1.f, 1.f, _a } { }
	hsv_color_t(float _h, float _s, float _v, float _a = 1.f) : channels{ _h, _s, _v, _a } { }

	hsv_color_t(const vec3_t<float> _hsv, float _a) : hsv_color_t{ _hsv.x, _hsv.y, _hsv.z, _a } { }
	hsv_color_t(const vec4_t<float> _hsva) : hsv_color_t{ _hsva.x, _hsva.y, _hsva.z, _hsva.w } { }
	hsv_color_t(const null::sdk::i_color<float>& rgba) : channels{ rgba.channels } {
		const double max{ std::ranges::max(rgba.channels | std::views::take(3)) };
		const double delta{ max - std::ranges::min(rgba.channels | std::views::take(3)) };

		if(delta <= 0.f) channels = { 0.f, 0.f, (float)max, rgba.a };
		else {
			if(max == rgba.r)			h = std::fmodf((rgba.g - rgba.b) / delta, 6.f);
			else if(max == rgba.g)	h = (rgba.b - rgba.r) / delta + 2.f;
			else if(max == rgba.b)	h = (rgba.r - rgba.g) / delta + 4.f;
			h *= 60.f;
			if(h < 0.f) h += 360.f;

			s = max > 0.f ? delta / max : 0.f;
			v = max;
		}
	}

public:
	fast_ops_structure_convert_operator(, vec3_t<float>() const, vec3_t<float>, , h, s, v);
	fast_ops_structure_convert_operator(, vec4_t<float>() const, vec4_t<float>, , h, s, v, a);

	operator null::sdk::i_color<float>() const {
		const double chroma{ v * s };
		const double prime{ std::fmod(h / 60.f, 6.f) };
		const double x{ chroma * (1.f - std::fabs(std::fmod(prime, 2.f) - 1.f)) };

		vec3_t<double> rgb{ };
		switch((int)prime) {
			case 0: rgb = { chroma, x,		0.f }; break;
			case 1: rgb = { x,		chroma,	0.f }; break;
			case 2: rgb = { 0.f,	chroma,	x }; break;
			case 3: rgb = { 0.f,	x,		chroma }; break;
			case 4: rgb = { x,		0.f,	chroma }; break;
			case 5: rgb = { chroma,	0.f,	x }; break;
		}

		const double m{ v - chroma };
		return null::sdk::i_color<double>{ rgb + m, a }.cast<float>();
	}

	fast_ops_structure_all_prefix_operators(h, s, v, a);
	fast_ops_structure_all_postfix_operators(h, s, v, a);

	fast_ops_structure_all_arithmetic_operators(template <typename self_t>, const hsv_color_t&, rhs_field, h, s, v, a);
	fast_ops_structure_all_arithmetic_operators(template <typename self_t>, float, rhs_value, h, s, v, a);

	fast_ops_structure_equal_operator(, const hsv_color_t&, rhs_field, h, s, v, a);
	fast_ops_structure_equal_operator(, float, rhs_value, h, s, v, a);

	fast_ops_structure_all_comparison_operators(template <typename self_t>, const hsv_color_t&, rhs_field, h, s, v, a);
	fast_ops_structure_all_comparison_operators(template <typename self_t>, float, rhs_value, h, s, v, a);
};