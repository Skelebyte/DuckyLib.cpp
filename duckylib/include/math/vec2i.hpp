#pragma once

#include <math.h>
#include <stdbool.h>

namespace ducky {

namespace math {

typedef union Vec2i {
  struct {
    int x;
    int y;
  };
  int data[2];
  Vec2i();
  Vec2i(int x_, int y_);
  void zero();
  float length() const;
  void normalize();

  Vec2i operator+(const Vec2i& other) const;
  Vec2i operator-(const Vec2i& other) const;
  void operator+=(const Vec2i& other);
  void operator-=(const Vec2i& other);
  bool operator==(const Vec2i& other) const;
} Vec2i, Vector2I;

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
