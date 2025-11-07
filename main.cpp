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

  EditorCamera camera = EditorCamera(&window);

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

  Keybind esc = Keybind(Keycode::ESC);
  Keybind disable = Keybind(Keycode::SPACE);
  Keybind size_up = Keybind(Keycode::U_ARROW);
  Keybind size_down = Keybind(Keycode::D_ARROW);

  Keybind lock_x = Keybind(Keycode::X);
  Keybind lock_y = Keybind(Keycode::Z);

  float s = 2.0f;

  std::cout << camera.field_of_view << "\n";
  std::cout << camera.near_plane << "\n";

  while (window.running()) {
    window.update();

    ducky_engine_keybinds();
    Renderer::clear_frame();
    EntityRegistry::update();

    cube2.transform.scale = Vec3(s);

    if (Input::get_key(&size_up)) {
      s += 0.1f * Time::delta_time();
    }

    if (Input::get_key(&size_down)) {
      s -= 0.1f * Time::delta_time();
    }

    std::cout << camera.transform.rotation.to_string() << std::endl;

    cube.transform.rotation.y += 45.0f * Time::delta_time();

    window.set_title(std::to_string(Time::fps()));

    window.swap();
  }

  return 0;
}
