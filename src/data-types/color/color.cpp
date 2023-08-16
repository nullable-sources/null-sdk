#include "color.h"

color_t<int>::color_t(float _r, float _g, float _b, float _a) : i_color{ color_t<float>{ _r, _g, _b, _a } } { }
color_t<int>::color_t(const i_color<float>& color) : i_color{ color_t<float>{ color } } { }

color_t<float>::color_t(int _r, int _g, int _b, int _a) : i_color{ color_t<int>{ _r, _g, _b, _a } } { }
color_t<float>::color_t(const i_color<int>& color) : i_color{ color_t<int>{ color } } { }