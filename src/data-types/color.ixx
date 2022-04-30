export module null.sdk:data_types.color;
#include <fast_operators.h>

struct color_t {
	enum class e_channels_type { bit8 /*0 - 255*/, arithmetic /*0.0 - 1.0*/ };
	std::array<float, 4> channels{};
	e_channels_type channels_type{};

	color_t() = default;
	color_t(color_t clr, int _a) : channels_type(clr.channels_type), channels(clr.channels) { if (clr.channels_type != e_channels_type::bit8) throw std::runtime_error("color channels type conflict"); a() = _a; }
	color_t(color_t clr, float _a) : channels_type(clr.channels_type), channels(clr.channels) { if (clr.channels_type != e_channels_type::arithmetic) throw std::runtime_error("color channels type conflict"); a() = _a; }
	color_t(float _r, float _g, float _b, float _a = 1.f) : channels_type(e_channels_type::arithmetic), channels({ _r, _g, _b, _a }) { }
	color_t(int _r, int _g, int _b, int _a = 255) : channels_type(e_channels_type::bit8), channels({ (float)_r, (float)_g, (float)_b, (float)_a }) { }

	float& r() { return channels[0]; }
	float& g() { return channels[1]; }
	float& b() { return channels[2]; }
	float& a() { return channels[3]; }

	template <typename channels_t>
	void set_channels_type() {
		if constexpr (std::is_same<channels_t, int>::value) channels_type = e_channels_type::bit8;
		else if constexpr (std::is_same<channels_t, float>::value) channels_type = e_channels_type::arithmetic;
		else throw std::runtime_error("wrong conversion type");
	}

	template <typename convert_t>
	color_t convert() {
		color_t converted;
		converted.set_channels_type<convert_t>();

		if (converted.channels_type == channels_type) return *this;

		std::transform(channels.begin(), channels.end(), converted.channels.begin(),
			[=](float& channel) { return channels_type == e_channels_type::bit8 ? channel / 255.f : channel * 255.f; });

		return converted;
	}

	class_create_spaceship_operator(color_t);
};