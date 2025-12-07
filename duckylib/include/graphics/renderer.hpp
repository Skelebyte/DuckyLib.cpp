#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "../../third_party/glad/glad.h"
#include "../ecs/entity.hpp"
#include "../math/vec2i.hpp"
#include "../math/vec3.hpp"
#include "../runtime_err.hpp"
#include "../time.hpp"
#include "color.hpp"

namespace ducky::ecs::entities {
class Light;
class PointLight;
class SpotLight;
class DirectionalLight;
class Camera;
}  // namespace ducky::ecs::entities

namespace ducky {
class Window;
}

namespace ducky::graphics {

class Shader;

typedef enum { BACK = 0, FRONT = 1 } FaceCullingType;

typedef struct {
  unsigned int max_point_lights;
  unsigned int max_spot_lights;
  unsigned int max_directional_lights;
  bool enable_blending;
  bool enable_depth_test;
  bool enable_culling;
  FaceCullingType culling_type;
  bool enable_line_smoothing;
  math::Vec2i shadow_map_size;
} RendererSettings;

class Renderer {
 public:
  static void init(RendererSettings renderer_settings = {
                       8, 8, 1, true, true, false, FaceCullingType::BACK, true,
                       math::Vec2i(2048, 2048)});
  static void clear_frame(Color color = Color(0.1f, 0.1f, 0.1f, 1.0f));
  static int get_max_point_lights();
  static int get_max_spot_lights();
  static int get_max_directional_lights();
  static void add_light(ducky::ecs::entities::Light* light);
  static void get_gl_error(std::string error_context = "");
  static void update_lights();
  static std::vector<ducky::ecs::entities::PointLight*> point_lights;
  static std::vector<ducky::ecs::entities::SpotLight*> spot_lights;
  static std::vector<ducky::ecs::entities::DirectionalLight*>
      directional_lights;
  static float ambient_strength;
  static ducky::math::Vec3 ambient_color;
  static void toggle_wireframe();
  static Shader* main_shader;
  static ecs::entities::Camera* main_camera;
  static Window* main_window;

 private:
  static bool wireframe_;
  static bool initialized_;
  static RendererSettings settings_;
  static unsigned int shadow_map_fbo_;
  static unsigned int shadow_map_;
};

}  // namespace ducky::graphics

/*
THE ISSUE
renderer.hpp includes light.hpp, which includes shader.hpp, which includes
renderer.hpp again
*/