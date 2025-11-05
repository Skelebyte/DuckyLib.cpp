#include <filesystem>
#define DUCKY_USE_NAMESPACES
#define DUCKY_ALLOW_ENGINE_KEYBINDS
#include "duckylib/ducky.hpp"

float sens = 2.0f;

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
  crate.unlit = true;

  MeshRenderer cube =
      MeshRenderer(&camera, cube_vertices, sizeof(cube_vertices), cube_indices,
                   sizeof(cube_indices), &shader, &crate);

  MeshRenderer cube2 =
      MeshRenderer(&camera, cube_vertices, sizeof(cube_vertices), cube_indices,
                   sizeof(cube_indices), &shader, &crate);
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
  Keybind size_up = Keybind(Keycode::U_ARROW);
  Keybind size_down = Keybind(Keycode::D_ARROW);

  float s = 2.0f;

  bool cursor = false;

  Vec2 last_mouse = Vec2(0, 0);
  bool first_mouse = true;

  while (window.running()) {
    window.update();

    ducky_engine_keybinds();
    Renderer::clear_frame();
    EntityRegistry::update();

    cube2.transform.scale = Vec3(s);

    if (Input::get_key(&size_up)) {
      s += 0.1f;
    }

    if (Input::get_key(&size_down)) {
      s -= 0.1f;
    }

    camera.transform.position +=
        Vec3::cross(camera.transform.forward(), camera.transform.up()) *
            Input::get_axis(axis_horizontal) * 0.02f +
        camera.transform.forward() * Input::get_axis(axis_vertical) * 0.02f +
        camera.transform.up() * Input::get_axis(axis_up) * 0.02f;

    if (Input::get_key_once(&disable)) {
      cube2.enabled = !cube2.enabled;
    }

    if (Input::get_key(&look)) {
      Vec2 mouse = Input::get_mouse_position(window);
      Input::cursor(window, true, false);

      if (first_mouse) {
        last_mouse = mouse;
        first_mouse = false;
      }

      Vec2 mouse_delta = mouse;
      //- last_mouse;
      last_mouse = mouse;

      float x = -mouse_delta.y * sens * window.get_viewport_aspect();
      float y = -mouse_delta.x * sens * window.get_viewport_aspect();

      camera.transform.rotation.x += x;
      camera.transform.rotation.y += y;

      camera.transform.rotation.x =
          std::clamp(camera.transform.rotation.x, -89.0f, 89.0f);

      std::cout << camera.transform.rotation.to_string() << "\n";

    } else {
      Input::cursor(window, false, false);
      first_mouse = true;
    }

    window.set_title(std::to_string(Time::fps()));

    window.swap();
  }

  return 0;
}
