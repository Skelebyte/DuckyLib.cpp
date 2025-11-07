#include <filesystem>
#define DUCKY_USE_NAMESPACES
#define DUCKY_ALLOW_ENGINE_KEYBINDS
#include "duckylib/ducky.hpp"

float sens = 0.001f;
float speed = 0.01f;

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

  Keybind lock_x = Keybind(Keycode::X);
  Keybind lock_y = Keybind(Keycode::Z);

  float s = 2.0f;

  bool cursor = false;

  Vec2 last_mouse = Vec2(0, 0);
  bool first_mouse = true;

  while (window.running()) {
    window.update();

    ducky_engine_keybinds();
    Renderer::clear_frame();

    cube2.transform.scale = Vec3(s);

    if (Input::get_key(&size_up)) {
      s += 0.1f * Time::delta_time();
    }

    if (Input::get_key(&size_down)) {
      s -= 0.1f * Time::delta_time();
    }

    cube.transform.rotation.y += 45.0f * Time::delta_time();

    camera.transform.position +=
        Vec3::cross(camera.transform.forward(), camera.transform.up())
                .normalized() *
            Input::get_axis(axis_horizontal) * speed * Time::delta_time() +
        camera.transform.forward() * Input::get_axis(axis_vertical) * speed *
            Time::delta_time() +
        camera.transform.up() * Input::get_axis(axis_up) * speed *
            Time::delta_time();

    if (Input::get_key_once(&disable)) {
      camera.transform.rotation.zero();
    }

    if (Input::get_key(&look)) {  // the rotation is in RADIANS for some reason.
      Vec2 mouse = Input::get_mouse_position(window);
      Input::cursor(window, true, false);

      if (first_mouse) {
        last_mouse = mouse;
        first_mouse = false;
      }

      Vec2 mouse_delta = mouse;
      last_mouse = mouse;

      float x = (-mouse_delta.y / 10) * sens * Time::delta_time();
      float y = (-mouse_delta.x / 10) * sens * Time::delta_time();

      if (!Input::get_key(&lock_x))
        camera.transform.rotation.x += Mathf::degrees(x);
      if (!Input::get_key(&lock_y))
        camera.transform.rotation.y += Mathf::degrees(y);

      camera.transform.rotation.x =
          std::clamp(camera.transform.rotation.x, -1.57f, 1.57f);

      std::cout << Vec3::cross(camera.transform.forward(),
                               camera.transform.up())
                       .normalized()
                       .to_string()
                << "\n";

    } else {
      Input::cursor(window, false, false);
      first_mouse = true;
    }

    window.set_title(std::to_string(Time::fps()));

    EntityRegistry::update();

    window.swap();
  }

  return 0;
}
