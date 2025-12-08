#pragma once

#include "app.hpp"
#include "ecs/entities/audio_player.hpp"
#include "ecs/entities/camera.hpp"
#include "ecs/entities/editor_camera.hpp"
#include "ecs/entities/light.hpp"
#include "ecs/entities/mesh_renderer.hpp"
#include "ecs/entities/ui/text.hpp"
#include "ecs/entity.hpp"
#include "ecs/entity_registry.hpp"
#include "ecs/level.hpp"
#include "ecs/transform.hpp"
#include "graphics/built_in_shaders.hpp"
#include "graphics/built_in_shapes.hpp"
#include "graphics/color.hpp"
#include "graphics/ebo.hpp"
#include "graphics/material.hpp"
#include "graphics/renderer.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "graphics/vao.hpp"
#include "graphics/vbo.hpp"
#include "input/input.hpp"
#include "math/mat4.hpp"
#include "math/mathf.hpp"
#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "object.hpp"
#include "object_registry.hpp"
#include "tools/asset_manager.hpp"
#include "utils/file.hpp"
#include "utils/to_string.hpp"
#include "window.hpp"

namespace ducky {
class Editor {
 public:
  static void update(ecs::Level& current_level);

 private:
  static unsigned int selected_entity;
  static char entity_name_[128];
  static const char* entity_types_[6];
  static int type_index_;
};
}  // namespace ducky