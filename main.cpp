#include "duckylib/include/app.hpp"
#include "duckylib/include/ecs/component.hpp"
#include "duckylib/include/ecs/components/camera_component.hpp"
#include "duckylib/include/ecs/components/mesh_renderer.hpp"
#include "duckylib/include/ecs/components/transform.hpp"
#include "duckylib/include/ecs/entity.hpp"
#include "duckylib/include/graphics/built_in_shaders.hpp"
#include "duckylib/include/graphics/built_in_shapes.hpp"
#include "duckylib/include/graphics/ebo.hpp"
#include "duckylib/include/graphics/renderer.hpp"
#include "duckylib/include/graphics/shader.hpp"
#include "duckylib/include/graphics/texture.hpp"
#include "duckylib/include/graphics/vao.hpp"
#include "duckylib/include/graphics/vbo.hpp"
#include "duckylib/include/input/input.hpp"
#include "duckylib/include/math/mat4.hpp"
#include "duckylib/include/math/mathf.hpp"
#include "duckylib/include/math/vec2.hpp"
#include "duckylib/include/math/vec3.hpp"
#include "duckylib/include/utils/file.hpp"
#include "duckylib/include/window.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::components;
using namespace ducky::graphics;
using namespace ducky::math;
using namespace ducky::input;

int main() {
  App app;
  Window window = Window("Hi mum!", 600, 600);

  Renderer::init();
  // Vertices coordinates
  GLfloat vertices[] = {
      //     COORDINATES     /        COLORS      /   TexCoord  //
      -0.5f, 0.0f,  0.5f,  0.83f, 0.70f, 0.44f, 0.0f,  0.0f,  -0.5f, 0.0f,
      -0.5f, 0.83f, 0.70f, 0.44f, 5.0f,  0.0f,  0.5f,  0.0f,  -0.5f, 0.83f,
      0.70f, 0.44f, 0.0f,  0.0f,  0.5f,  0.0f,  0.5f,  0.83f, 0.70f, 0.44f,
      5.0f,  0.0f,  0.0f,  0.8f,  0.0f,  0.92f, 0.86f, 0.76f, 2.5f,  5.0f};

  GLuint indices[] = {0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};

  Shader shader =
      Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

  Texture texture = Texture();

  Entity main_camera = Entity("camera");
  Transform* camera_transform = main_camera.add_component(new Transform());
  CameraComponent* camera =
      main_camera.add_component(new CameraComponent(camera_transform, &window));

  Entity mesh = Entity("mesh");
  Transform* mesh_t = mesh.add_component(new Transform());
  MeshRenderer* mesh_mr = mesh.add_component(new MeshRenderer(
      mesh_t, camera, pyramid_vertices, sizeof(pyramid_vertices),
      pyramid_indices, sizeof(pyramid_indices), shader, texture));

  mesh_t->position = Vec3(0.0f, -0.5f, -2.0f);

  InputAxis axis_horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis axis_vertical = InputAxis(Keycode::W, Keycode::S);
  Keybind esc = Keybind(Keycode::ESC);
  bool cursor = false;

  while (window.running()) {
    window.poll();

    Renderer::clear_frame();

    main_camera.update();
    mesh.update();

    camera_transform->position.x += -Input::get_axis(axis_horizontal) * 0.05f;
    camera_transform->position.z += Input::get_axis(axis_vertical) * 0.05f;

    camera_transform->rotation.x = Input::get_mouse_position(window).y * 100;
    camera_transform->rotation.y = -Input::get_mouse_position(window).x * 100;

    if (Input::get_key(esc, true)) {
      cursor = !cursor;
    }
    Input::cursor(window, cursor, false);
    window.render();
  }

  return 0;
}
