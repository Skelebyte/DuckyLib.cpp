#include <filesystem>
#define DUCKY_USE_NAMESPACES
#define DUCKY_ALLOW_ENGINE_KEYBINDS
#include "duckylib/ducky.hpp"

// int main(int argc, char** argv) {
//   ducky::App app(argv[1]);
//   ducky::Window window("Ducky Engine", 1280, 720);

//   while (window.running()) {
//     window.update();
//     ducky_engine_keybinds();
//     Renderer::clear_frame();

//     window.swap();
//   }

//   return 0;
// }

int main(int argc, char** argv) {
  App app(argv[1]);
  Window window("Hi mum!", 1000, 800);

  Renderer::ambient_color = Vec3(0.3f);

  Shader shader;
  EditorCamera camera(&window);

  Material crate(Texture("assets/textures/container_diffuse.png"),
                 Texture("assets/textures/container_specular.png"),
                 Color::white());
  crate.specular_strength = 1.0f;
  crate.unlit = true;

  MeshRenderer cube(&camera, cube_vertices, sizeof(cube_vertices), cube_indices,
                    sizeof(cube_indices), &shader, &crate);
  MeshRenderer cube2(&camera, cube_vertices, sizeof(cube_vertices),
                     cube_indices, sizeof(cube_indices), &shader, &crate);
  cube2.transform.position.z = 2.0f;
  cube2.transform.scale = Vec3(0.1f);

  DirectionalLight sun;
  sun.transform.rotation = Vec3(1.0f);
  sun.color = Color(0.98f, 0.94f, 0.8f, 1.0f);
  Renderer::add_light(&sun);

  Keybind esc(Keycode::ESC);
  Keybind size_up(Keycode::U_ARROW);
  Keybind size_down(Keycode::D_ARROW);

  float s = 2.0f;

  while (window.running()) {
    window.update();
    ducky_engine_keybinds();
    Renderer::clear_frame();
    EntityRegistry::update();

    ImGui::Begin("Interactions!");
    ImGui::InputFloat3("Position", cube.transform.position.data);
    ImGui::InputFloat3("Rotation", cube.transform.rotation.data);
    ImGui::InputFloat3("Scale", cube.transform.scale.data);
    ImGui::End();

    if (Input::get_key(&size_up))
      s += 0.1f * Time::delta_time();
    if (Input::get_key(&size_down))
      s -= 0.1f * Time::delta_time();

    cube2.transform.scale = Vec3(s);

    window.set_title(std::to_string(Time::fps()));
    window.swap();
  }
}
