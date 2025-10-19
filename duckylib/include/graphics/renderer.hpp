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

typedef enum {
  BACK = 0,
  FRONT = 1
} FaceCullingType;

typedef struct {
  unsigned int max_lights;
  bool enable_blending;
  bool enable_depth_test;
  bool enable_culling;
  FaceCullingType culling_type;  
  bool enable_line_smoothing;
} RendererSettings;

class Renderer {
 public:
  static void init(RendererSettings renderer_settings = {8, true, true, true, FaceCullingType::BACK, true});
  static void clear_frame(Color color = Color(0.1f, 0.1f, 0.1f, 1.0f));
  static int get_max_lights();
  static void add_light(ducky::ecs::entities::Light* light);
  static void update_lights();
  static std::vector<ducky::ecs::entities::Light*> lights;
  static void get_gl_error(std::string error_context = "");

 private:
  static bool initialized_;
  static RendererSettings settings_;
};

}  // namespace ducky::graphics

/*
THE ISSUE
renderer.hpp includes light.hpp, which includes shader.hpp, which includes
renderer.hpp again
*/