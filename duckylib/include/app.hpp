#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <iostream>
#include <memory>
#include "../third_party/imgui/imgui.h"
#include "../third_party/imgui/imgui_impl_opengl3.h"
#include "../third_party/imgui/imgui_impl_sdl3.h"
#include "ecs/entities/camera.hpp"
#include "ecs/entities/editor_camera.hpp"
#include "ecs/entities/light.hpp"
#include "ecs/entities/mesh_renderer.hpp"
#include "ecs/entity.hpp"
#include "ecs/entity_registry.hpp"
#include "graphics/built_in_shapes.hpp"
#include "graphics/renderer.hpp"
#include "graphics/shader.hpp"
#include "runtime_err.hpp"
#include "time.hpp"

namespace ducky {
class App {
 public:
  App(const char* arg);
  ~App();
  void dev_ui_update();
  static std::string set_project_name();
  static std::string get_project_name();

 private:
  bool dev_mode_ = false;
  std::string project_name_;

  unsigned int selected_entity = -1;

  char name[128] = {};
  const char* types[4] = {"MeshRenderer", "PointLight", "SpotLight",
                          "DirectionalLight"};
  int type_index = 0;
  bool spawn_zeroed = true;
};
}  // namespace ducky