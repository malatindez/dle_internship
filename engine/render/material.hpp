#pragma once
#include "core/math.hpp"
namespace engine::render
{
  class Material final
  {
  public:
    core::math::vec3 albedo{1.0f};
    core::math::vec3 emission{0.0f};
    core::math::vec3 F0{0.5f};
    float roughness = 0.5f;
    float metalness = 0.5f; 
    bool casts_shadow = true;
  };
} // namespace engine::render