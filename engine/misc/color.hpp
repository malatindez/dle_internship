#pragma once
#include "math.hpp"
namespace engine
{
    struct Color : math::vec<3, float>
    {
        using math::vec<3, float>::vec;
    };
} // namespace engine