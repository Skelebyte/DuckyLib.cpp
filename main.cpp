#include "duckylib/ducky.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::components;
using namespace ducky::graphics;
using namespace ducky::math;
using namespace ducky::input;

float x_rot;

int main() {
  App app;
  Window window = Window("Hi mum!", 1000, 800);

  Renderer::init();

  Shader shader =
      Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

  Texture texture = Texture("assets/textures/frank.png");

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

    float x = Input::get_mouse_position(window).x;
    float y = -Input::get_mouse_position(window).y;

    camera_transform->rotation.x = y * 100;
    camera_transform->rotation.y = x * 100;

    Vec3 move = Vec3();

    move += camera_transform->forward() * -Input::get_axis(axis_vertical);
    move += camera_transform->right() * -Input::get_axis(axis_horizontal);

    camera_transform->position += move * 0.01f;

    if (Input::get_key(esc, true)) {
      cursor = !cursor;
    }
    Input::cursor(window, cursor, false);
    window.render();
  }

  return 0;
}
