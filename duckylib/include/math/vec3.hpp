#pragma once

#include <math.h>
#include <stdbool.h>
#include <iostream>
#include <string>
#include "pi.hpp"

namespace ducky {

namespace math {

typedef struct Vec3 {
  union {
    struct {
      float x, y, z;
    };
    float data[3];
  };
  Vec3();
  Vec3(float x_, float y_, float z_);
  void zero();
  void rotate(float angle, Vec3 axis);
  float length() const;
  Vec3 normalized();
  static float dot(Vec3 a, Vec3 b);
  static Vec3 cross(Vec3 a, Vec3 b);
  std::string to_string() const;

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(const Vec3& other) const;
  Vec3 operator*(const float& other) const;
  void operator+=(const Vec3& other);
  void operator-=(const Vec3& other);
  bool operator==(const Vec3& other) const;

} Vec3, Vector3;

}  // namespace math

}  // namespace ducky

// Vec3 vec3_zero();
// Vec3 vec3(float x, float y, float z);
// Vec3 vec3_add(Vec3 a, Vec3 b);
// Vec3 vec3_sub(Vec3 a, Vec3 b);
// float vec3_dot(Vec3 a, Vec3 b);
// float vec3_length(Vec3 vec);
// float vec3_magnitude(Vec3 vec);
// Vec3 vec3_normalize(Vec3 vec);
// bool vec3_is_equal(Vec3 a, Vec3 b);
// Vec3 vec3_cross(Vec3 a, Vec3 b);
