#include "vec.hpp"
namespace engine::core::math
{
    template struct vec<2, float>;
    template struct vec<2, double>;
    template struct vec<2, int>;
    template struct vec<3, float>;
    template struct vec<3, double>;
    template struct vec<3, int>;
    template struct vec<4, float>;
    template struct vec<4, double>;
    template struct vec<4, int>;

    template struct rvec<2, float>;
    template struct rvec<2, double>;
    template struct rvec<2, int>;
    template struct rvec<3, float>;
    template struct rvec<3, double>;
    template struct rvec<3, int>;
    template struct rvec<4, float>;
    template struct rvec<4, double>;
    template struct rvec<4, int>;
} // namespace engine::core::math