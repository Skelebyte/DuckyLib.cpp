#pragma once

#include <iostream>

namespace ducky {

namespace graphics {

typedef struct Color {
  union {
    struct {
      float r, g, b, a;
    };
    float data[4];
  };
  Color();
  Color(float r_, float g_, float b_, float a_);

  static Color white();
  static Color black();
  static Color grey();
  static Color pink();
  static Color red();
  static Color green();
  static Color blue();

} Color, RGBA;

}  // namespace graphics

}  // namespace ducky