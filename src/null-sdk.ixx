module;
#include <xstring> //@note: DO NOT TOUCH THIS, otherwise overridden methods inside which std::map / unordered_map is used will not be compiled
export module null.sdk;

//@note: to use fast_operators you need to include it separately

export import :math.matrix;
export import :math.matrix2x2;
export import :math.matrix3x3;
export import :math.matrix4x4;

export import :math.vec2;
export import :math.vec3;
export import :math.vec4;

export import :math.angle;
export import :math.rect;

export import :math.geometry;
export import :math;

export import :utils.color;
export import :utils.compatibility_type_converter;
export import :utils.time_measurement;
export import :utils.callbacks;
export import :utils.win.console;
export import :utils.win;
export import :utils.events;
export import :utils.logger;

export import :utils.encoding;
export import :utils.encoding.base85;

export import :memory.address;
export import :memory.minhook_wrapper;
export import :memory.win_module.dll;
export import :memory.win_module;
export import :memory.dll_export;
export import :memory.dll_export_view;
export import :memory.pe_image;
export import :memory.resource;
export import :memory.signature;