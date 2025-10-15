#include "duckylib/ducky.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::components;
using namespace ducky::ecs::entities;
using namespace ducky::graphics;
using namespace ducky::math;
using namespace ducky::input;

float sens = 10.0f;

int main(int argc, char** argv) {
  App app(argv[1]);

  Window window = Window("Hi mum!", 1000, 800);

  Renderer::init();

  Shader shader = Shader();

  Camera camera = Camera(&window);

  MeshRenderer pyramid = MeshRenderer(
      &camera, pyramid_vertices, sizeof(pyramid_vertices), pyramid_indices,
      sizeof(pyramid_indices), &shader, Texture("assets/textures/frank.png"));

  pyramid.transform.position = Vec3(0.0f, -0.5f, -2.0f);

  MeshRenderer mesh =
      MeshRenderer(&camera, cube_vertices, sizeof(cube_vertices), cube_indices,
                   sizeof(cube_indices), &shader, Texture(EMPTY_TEXTURE));
  mesh.transform.scale = Vec3(0.1f, 0.1f, 0.1f);

  Light light = Light();
  Light light2 = Light();
  Renderer::add_light(&light);
  Renderer::add_light(&light2);
  light.color = Color::blue();
  light2.color = Color::red();

  InputAxis axis_horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis axis_vertical = InputAxis(Keycode::W, Keycode::S);
  InputAxis axis_up = InputAxis(Keycode::Q, Keycode::E);
  Keybind esc = Keybind(Keycode::ESC);
  Keybind look = Keybind(Keycode::LMB);
  bool cursor = false;

  while (window.running()) {
    window.poll();

    Renderer::clear_frame();
    Renderer::update_lights();

    camera.update();
    pyramid.update();
    mesh.update();

    light2.transform.position = camera.transform.position;

    camera.transform.position +=
        Vec3::cross(camera.get_orientation(), camera.transform.up()) *
            Input::get_axis(axis_horizontal) * 0.01f +
        camera.get_orientation() * Input::get_axis(axis_vertical) * 0.01f +
        camera.transform.up() * Input::get_axis(axis_up) * 0.01f;

    if (Input::get_key(look)) {
      Vec2 mouse = Input::get_mouse_position(window);
      Vec2i dimensions = window.get_dimensions();

      float x = -mouse.x * dimensions.x * sens;
      float y = mouse.y * dimensions.y * sens;

      camera.transform.rotation = Vec3(y, x, 0.0f);
      // Input::cursor(window, true, false);
    } else {
      Input::cursor(window, false, false);
    }

    window.render();
    // window.stop();
  }

  return 0;
}
