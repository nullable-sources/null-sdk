#pragma once
#include <format>
#include <numeric>
#include <ranges>
#include <fstream>

#include "null-sdk/utils/win/win.h"

#include "null-sdk/memory/address.h"
#include "null-sdk/memory/signature.h"
#include "null-sdk/memory/pe-image.h"
#include "null-sdk/memory/module/module.h"
#include "null-sdk/memory/minhook-wrapper.h"
#include "null-sdk/memory/resource/resource.h"

#include "null-sdk/utils/logger/logger.h"

#include "null-sdk/utils/encoding/encoding.h"

#include "null-sdk/utils/time-measurement/time-measurement.h"

#include "null-sdk/math/math.h"
#include "null-sdk/data-types/matrix/matrix4x4.h"
#include "null-sdk/data-types/matrix/matrix3x3.h"
#include "null-sdk/data-types/matrix/matrix2x2.h"
#include "null-sdk/data-types/color/hsv.h"
#include "null-sdk/data-types/callbacks.h"
#include "null-sdk/data-types/angle/euler2d.h"
#include "null-sdk/data-types/angle/quaternion.h"