#include "angle.h"

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