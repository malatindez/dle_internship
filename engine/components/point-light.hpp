#pragma once
#include "math.hpp"
#include "light-data.hpp"
#include <cmath>
namespace engine::components
{
    struct PointLight
    {
        math::vec3 color;
        float ambient_intensity;
        float diffuse_intensity;
        float specular_intensity;
        struct Attenuation
        {
            float constant;
            float linear;
            float quadratic;
        } attenuation;

        
        void UpdateColor(Transform &transform, LightData &light_data) const
        {
            math::vec3 const light_direction = - light_data.point + transform.position;
            float const t = math::dot(light_data.normal, light_direction);
            light_data.color += color * ambient_intensity;
            if (t < 0)
            {
                return;
            }
            float distance = math::length(light_direction);
            float attenuation = 1.0f /
                                (this->attenuation.constant +
                                 this->attenuation.linear * distance +
                                 this->attenuation.quadratic * distance * distance);

            math::vec3 const reflect_dir = math::normalize(2.0f * 
                    math::dot(light_data.normal, light_direction) * 
                    (light_data.normal - light_direction));
            
            float diffuse = attenuation * diffuse_intensity * t;
            float u = dot(light_data.view_dir, reflect_dir);
            float specular = attenuation* specular_intensity* static_cast<float>(std::pow(std::max(u, 0.0f), 32));
            
            light_data.color += color * (ambient_intensity + diffuse + specular);
            
        }
    };
} // namespace engine