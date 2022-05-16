#pragma once

#include "math/mat.hpp"
#include "math/mat_math.hpp"
#include "math/vec.hpp"
#include "math/vec_math.hpp"

#include <cmath>
#include <type_traits>
#include <algorithm>
#include <limits>

namespace engine::math
{
    template<class T>
    bool almost_equal(T x, T y, int ulp = 2) requires (!std::numeric_limits<T>::is_integer)
    {
        // the machine epsilon has to be scaled to the magnitude of the values used
        // and multiplied by the desired precision in ULPs (units in the last place)
        return std::fabs(x - y) <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulp
            // unless the result is subnormal
            || std::fabs(x - y) < std::numeric_limits<T>::min();
    }
}