#include <filesystem>
#define DUCKY_USE_NAMESPACES
#include "duckylib/ducky.hpp"

float sens = 10.0f;

int main(int argc, char** argv) {
  App app(argv[1]);

  Window window = Window("Hi mum!", 1000, 800);

  Renderer::ambient_color = Vec3(0.3f, 0.3f, 0.3f);

  Shader shader = Shader();

  Camera camera = Camera(&window);

  Material crate = Material(Texture("assets/textures/container_diffuse.png"),
                            Texture("assets/textures/container_specular.png"),
                            Color::white());
  crate.specular_strength = 1.0f;

  MeshRenderer cube =
      MeshRenderer(&camera, cube_vertices, sizeof(cube_vertices), cube_indices,
                   sizeof(cube_indices), &shader, crate);

  MeshRenderer cube2 =
      MeshRenderer(&camera, cube_vertices, sizeof(cube_vertices), cube_indices,
                   sizeof(cube_indices), &shader, crate);
  cube2.transform.position.z = 2;
  cube2.transform.scale = Vec3(0.1f);
  DirectionalLight sun = DirectionalLight();
  Renderer::add_light(&sun);
  sun.transform.rotation = Vec3(1.0f, 1.0f, 1.0f);
  sun.color = Color(0.98f, 0.94f, 0.8f, 1.0f);

  InputAxis axis_horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis axis_vertical = InputAxis(Keycode::W, Keycode::S);
  InputAxis axis_up = InputAxis(Keycode::Q, Keycode::E);
  Keybind esc = Keybind(Keycode::ESC);
  Keybind look = Keybind(Keycode::LMB);
  Keybind disable = Keybind(Keycode::SPACE);

  bool cursor = false;

  while (window.running()) {
    window.update();

    Renderer::clear_frame();
    EntityRegistry::update();

    camera.transform.position +=
        Vec3::cross(camera.transform.forward(), camera.transform.up()) *
            Input::get_axis(axis_horizontal) * 0.01f +
        camera.transform.forward() * Input::get_axis(axis_vertical) * 0.01f +
        camera.transform.up() * Input::get_axis(axis_up) * 0.01f;

    if (Input::get_key_once(&disable)) {
      cube2.enabled = !cube2.enabled;
    }

    if (Input::get_key(&look)) {
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
