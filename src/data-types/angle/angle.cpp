#include <data-types/angle/angle.h>

angle_t<radians_t>::angle_t(const angle_t<degrees_t>& degrees) : i_angle{ degrees.cast() } { }
angle_t<radians_t>::angle_t(const degrees_t& degrees) : i_angle{ degrees * pi } { }

degrees_t angle_t<radians_t>::cast() const { return value * pi; }
angle_t<radians_t>::operator degrees_t() const { return cast(); }
angle_t<radians_t>::operator angle_t<degrees_t>() const { return angle_t<degrees_t>{ cast() }; }

angle_t<degrees_t>::angle_t(const angle_t<radians_t>& radians) : i_angle{ radians.cast() } { }
angle_t<degrees_t>::angle_t(const radians_t& radians) : i_angle{ radians * pi } { }

radians_t angle_t<degrees_t>::cast() const { return value * pi; }
angle_t<degrees_t>::operator radians_t() const { return cast(); }
angle_t<degrees_t>::operator angle_t<radians_t>() const { return angle_t<radians_t>{ cast() }; }