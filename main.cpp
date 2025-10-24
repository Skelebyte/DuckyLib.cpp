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

  Renderer::ambient_color = Vec3(0.3f, 0.3f, 0.3f);

  Shader shader = Shader();

  Camera camera = Camera(&window);

  Material crate = Material(Texture("assets/textures/container_diffuse.png"),
                            Texture(DEFAULT_TEXTURE), Color::white());
  crate.specular_strength = 1.0f;

  MeshRenderer cube =
      MeshRenderer(&camera, cube_vertices, sizeof(cube_vertices), cube_indices,
                   sizeof(cube_indices), &shader, crate);

  DirectionalLight sun = DirectionalLight();
  Renderer::add_light(&sun);
  sun.transform.rotation = Vec3(1.0f, 1.0f, 1.0f);
  sun.color = Color(0.98f, 0.94f, 0.8f, 1.0f);

  InputAxis axis_horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis axis_vertical = InputAxis(Keycode::W, Keycode::S);
  InputAxis axis_up = InputAxis(Keycode::Q, Keycode::E);
  Keybind esc = Keybind(Keycode::ESC);
  Keybind look = Keybind(Keycode::LMB);

  bool cursor = false;

  while (window.running()) {
    window.update();

    Renderer::clear_frame();

    camera.update();
    cube.update();

    camera.transform.position +=
        Vec3::cross(camera.transform.forward(), camera.transform.up()) *
            Input::get_axis(axis_horizontal) * 0.01f +
        camera.transform.forward() * Input::get_axis(axis_vertical) * 0.01f +
        camera.transform.up() * Input::get_axis(axis_up) * 0.01f;

    if (Input::get_key(look)) {
      Vec2 mouse = Input::get_mouse_position(window);
      Vec2i dimensions = window.get_dimensions();

      float x = -mouse.x * dimensions.x * sens;
      float y = mouse.y * dimensions.y * sens;

      camera.transform.rotation = Vec3(y, x, 0.0f);

    } else {
      Input::cursor(window, false, false);
    }

    window.swap();
  }

  return 0;
}
