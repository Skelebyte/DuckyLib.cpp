#pragma once

#include <cmath>
#include <iostream>
#include "mat4.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

namespace ducky {

namespace math {

class Mathf {
 public:
  static float to_radians(float value);
  static float to_degrees(float value);
  // Vec2 v3_to_v2(Vec3 value);
  // Vec3 v2_to_v3(Vec2 value, float z_value);
};

}  // namespace math

}  // namespace ducky
