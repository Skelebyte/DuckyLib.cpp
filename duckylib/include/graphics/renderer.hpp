#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include "../../third_party/glad/glad.h"

namespace ducky {

namespace graphics {

class Renderer {
 public:
  static void init();
  static void clear_frame(float r = 0.1f, float g = 0.1f, float b = 0.1f);
};

}  // namespace graphics

}  // namespace ducky