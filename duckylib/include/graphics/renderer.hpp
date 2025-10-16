#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "../../third_party/glad/glad.h"
#include "../runtime_err.hpp"
#include "color.hpp"

namespace ducky::ecs::entities {
class Light;
}

namespace ducky::graphics {
class Renderer {
 public:
  static void init(int max_point_lights = 8);
  static void clear_frame(Color color = Color(0.1f, 0.1f, 0.1f, 1.0f));
  static int get_max_lights();
  static void add_light(ducky::ecs::entities::Light* light);
  static void update_lights();
  static std::vector<ducky::ecs::entities::Light*> lights;
  static void get_gl_error(std::string error_context = "");

 private:
  static int max_lights_;
};

}  // namespace ducky::graphics

/*
      THE ISSUE
renderer.hpp includes light.hpp, which includes shader.hpp, which includes
renderer.hpp again
*/