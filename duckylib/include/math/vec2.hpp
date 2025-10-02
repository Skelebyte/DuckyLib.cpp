#pragma once

#include <math.h>
#include <stdbool.h>

namespace ducky {

namespace math {

typedef union Vec2 {
  struct {
    float x;
    float y;
  };
  float data[2];
  Vec2();
  Vec2(float x_, float y_);
  void zero();
  float length() const;
  Vec2 normalized();

  Vec2 operator+(const Vec2& other) const;
  Vec2 operator-(const Vec2& other) const;
  void operator+=(const Vec2& other);
  void operator-=(const Vec2& other);
  bool operator==(const Vec2& other) const;
} Vec2, Vector2;

}  // namespace math

// Vec2 vec2_add(Vec2 a, Vec2 b);
// Vec2 vec2_sub(Vec2 a, Vec2 b);
// float vec2_dot(Vec2 a, Vec2 b);
// float vec2_length(Vec2 vec);
// float vec2_magnitude(Vec2 vec);
// Vec2 vec2_normalize(Vec2 vec);
// bool vec2_is_equal(Vec2 a, Vec2 b);
// Vec2 vec2_cross(Vec2 a, Vec2 b);
// float vec2_distance(Vec2 a, Vec2 b);
}  // namespace ducky
