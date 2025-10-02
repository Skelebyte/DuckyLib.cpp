#pragma once

#include <math.h>
#include <stdbool.h>

namespace ducky {

namespace math {

typedef union Vec2I {
  struct {
    int x;
    int y;
  };
  int data[2];
  Vec2I();
  Vec2I(int x_, int y_);
  void zero();
  float length() const;
  void normalize();

  Vec2I operator+(const Vec2I& other) const;
  Vec2I operator-(const Vec2I& other) const;
  void operator+=(const Vec2I& other);
  void operator-=(const Vec2I& other);
  bool operator==(const Vec2I& other) const;
} Vec2I, Vector2I;

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
