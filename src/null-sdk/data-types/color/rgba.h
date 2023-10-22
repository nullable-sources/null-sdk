#pragma once
#include "color.h"

template <typename channel_t>
struct color_t { };

template <>
struct color_t<int> : public null::sdk::i_color<int> {
public:
	struct palette_t {
	public:
		static constexpr i_color<int> white	{ 255,	255,	255,	255 };
		static constexpr i_color<int> black	{ 0,	0,		0,		255 };
		static constexpr i_color<int> red	{ 255,	0,		0,		255 };
		static constexpr i_color<int> green	{ 0,	255,	0,		255 };
		static constexpr i_color<int> blue	{ 0,	0,		255,	255 };
	};

public:
	using i_color::i_color;
	inline constexpr color_t() : i_color(255) { }

	inline constexpr color_t(float _rgba) : i_color((int)(_rgba * 255.f)) { }

	inline constexpr color_t(int _rgb, float _a) : i_color(_rgb, (int)(_a * 255.f)) { }
	inline constexpr color_t(float _rgb, int _a) : i_color((int)(_rgb * 255.f), _a) { }
	inline constexpr color_t(float _rgb, float _a) : i_color((int)(_rgb * 255.f), (int)(_a * 255.f)) { }

	inline constexpr color_t(int _r, int _g, int _b, int _a = 255) : i_color(_r, _g, _b, _a) { }
	inline constexpr color_t(float _r, float _g, float _b, float _a = 1.f);

	inline constexpr color_t(const i_color<int>& color) : i_color(color) { }
	inline constexpr color_t(const i_color<int>& color, float _a) : i_color(color, (int)(_a * 255.f)) { }
	inline constexpr color_t(const i_color<float>& color);

public:
	inline constexpr operator i_color<float>() const { return cast<float>() / 255.f; }
};

template <>
struct color_t<float> : null::sdk::i_color<float> {
public:
	struct palette_t {
	public:
		static constexpr i_color<float> white	{ 1.f, 1.f, 1.f, 1.f };
		static constexpr i_color<float> black	{ 0.f, 0.f, 0.f, 1.f };
		static constexpr i_color<float> red		{ 1.f, 0.f, 0.f, 1.f };
		static constexpr i_color<float> green	{ 0.f, 1.f, 0.f, 1.f };
		static constexpr i_color<float> blue	{ 0.f, 0.f, 1.f, 1.f };
	};

public:
	using i_color::i_color;
	inline constexpr color_t() : i_color(1.f) { }

	inline constexpr color_t(int _rgba) : i_color((float)_rgba / 255.f) { }

	inline constexpr color_t(float _rgb, int _a) : i_color(_rgb, (float)_a / 255.f) { }
	inline constexpr color_t(int _rgb, float _a) : i_color((float)_rgb / 255.f, _a) { }
	inline constexpr color_t(int _rgb, int _a) : i_color((float)_rgb / 255.f, (float)_a / 255.f) { }

	inline constexpr color_t(float _r, float _g, float _b, float _a = 1.f) : i_color(_r, _g, _b, _a) { }
	inline constexpr color_t(int _r, int _g, int _b, int _a = 255);

	inline constexpr color_t(const i_color<float>& color) : i_color(color) { }
	inline constexpr color_t(const i_color<float>& color, int _a) : i_color(color, _a / 255.f) { }
	inline constexpr color_t(const i_color<int>& color);

private:
	template <typename self_t> inline auto&& round(this self_t&& self) { std::ranges::transform(self.channels, self.channels.begin(), std::roundf); return self; }

public:
	inline constexpr operator i_color<int>() const { return color_t<float>(*this * 255).round().cast<int>(); }
};

inline constexpr color_t<int>::color_t(float _r, float _g, float _b, float _a) : i_color(color_t<float>(_r, _g, _b, _a)) { }
inline constexpr color_t<int>::color_t(const i_color<float>& color) : i_color(color_t<float>(color)) { }

inline constexpr color_t<float>::color_t(int _r, int _g, int _b, int _a) : i_color(color_t<int>(_r, _g, _b, _a)) { }
inline constexpr color_t<float>::color_t(const i_color<int>& color) : i_color(color_t<int>(color)) { }