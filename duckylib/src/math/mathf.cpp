#include "../../include/math/mathf.hpp"

using namespace ducky;
using namespace ducky::math;

float Mathf::to_radians(float value) { return value * M_PI / 180; }

// Vec2 Fmath::v3_to_v2(Vec3 value) { return Vec2(value.x, value.y); }

// Vec3 Fmath::v2_to_v3(Vec2 value, float z_value) {
//   return vec3(value.x, value.y, z_value);
// }