#include "data-types/angle/angle.h"

angle_t<radians_t>::angle_t(const i_angle<degrees_t>& degrees) : angle_t{ degrees.value } { }
angle_t<radians_t>::angle_t(const angle_t<degrees_t>& degrees) : i_angle{ degrees.cast() } { }
angle_t<radians_t>::angle_t(degrees_t degrees) : i_angle{ degrees * angle_t<degrees_t>::pi } { }
angle_t<radians_t>::operator angle_t<degrees_t>() const { return angle_t<degrees_t>{ cast() }; }


angle_t<degrees_t>::angle_t(const i_angle<radians_t>& radians) : angle_t{ radians.value } { }
angle_t<degrees_t>::angle_t(const angle_t<radians_t>& radians) : i_angle{ radians.cast() } { }
angle_t<degrees_t>::angle_t(radians_t radians) : i_angle{ degrees_t(radians * angle_t<radians_t>::pi) } { }
angle_t<degrees_t>::operator angle_t<radians_t>() const { return angle_t<radians_t>{ cast() }; }

#define make_function(type, name, body) type angle_t<type>::name##() const { return body; }

#define make_degrees_functuin(name) make_function(degrees_t, name, std::name##(cast()) * angle_t<radians_t>::pi)
#define make_radians_functuin(name) make_function(radians_t, name, std::name##(value))

#define make_functions(type, name) type(name) type(a##name) type(name##h) type(a##name##h)	

make_functions(make_degrees_functuin, sin);
make_functions(make_degrees_functuin, cos);
make_functions(make_degrees_functuin, tan);

make_functions(make_radians_functuin, sin);
make_functions(make_radians_functuin, cos);
make_functions(make_radians_functuin, tan);