#pragma once
#include <format>
#include <numeric>
#include <ranges>
#include <fstream>

#include "utils/memory/address.h"
#include "utils/memory/signature.h"
#include "utils/memory/pe_image.h"
#include "utils/memory/module/module.h"
#include "utils/memory/minhook-wrapper.h"
#include "utils/memory/resource/resource.h"

#include "utils/logger/logger.h"

#include "utils/encoding/encoding.h"

#include "utils/time-measurement/time-measurement.h"

#include "math/math.h"
#include "data-types/matrix/matrix4x4.h"
#include "data-types/matrix/matrix3x3.h"
#include "data-types/matrix/matrix2x2.h"
#include "data-types/color.h"
#include "data-types/callbacks.h"