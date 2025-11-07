#include "include/app.hpp"
#include "include/ecs/entities/camera.hpp"
#include "include/ecs/entities/editor_camera.hpp"
#include "include/ecs/entities/light.hpp"
#include "include/ecs/entities/mesh_renderer.hpp"
#include "include/ecs/entity.hpp"
#include "include/ecs/entity_registry.hpp"
#include "include/ecs/transform.hpp"
#include "include/graphics/built_in_shaders.hpp"
#include "include/graphics/built_in_shapes.hpp"
#include "include/graphics/color.hpp"
#include "include/graphics/ebo.hpp"
#include "include/graphics/material.hpp"
#include "include/graphics/renderer.hpp"
#include "include/graphics/shader.hpp"
#include "include/graphics/texture.hpp"
#include "include/graphics/vao.hpp"
#include "include/graphics/vbo.hpp"
#include "include/input/input.hpp"
#include "include/math/mat4.hpp"
#include "include/math/mathf.hpp"
#include "include/math/vec2.hpp"
#include "include/math/vec3.hpp"
#include "include/object.hpp"
#include "include/object_registry.hpp"
#include "include/tools/asset_manager.hpp"
#include "include/utils/file.hpp"
#include "include/utils/to_string.hpp"
#include "include/window.hpp"

#ifdef DUCKY_USE_NAMESPACES
using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::graphics;
using namespace ducky::math;
using namespace ducky::input;
using namespace ducky::tools;
using namespace ducky::utils;
#endif

#ifdef DUCKY_ALLOW_ENGINE_KEYBINDS
namespace ducky {
input::Keybind ducky_toggle_wireframe = input::Keybind(input::Keycode::F1);

static void ducky_engine_keybinds() {
  if (Input::get_key_once(&ducky_toggle_wireframe)) {
    Renderer::toggle_wireframe();
  }
}
}  // namespace ducky
#endif