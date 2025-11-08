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

  unsigned int selected_entity = -1;

  while (window.running()) {
    window.update();
    ducky_engine_keybinds();
    Renderer::clear_frame();
    EntityRegistry::update();

    ImGui::Begin("Entities");
    for (int i = 0; i < EntityRegistry::get_entities().size(); i++) {
      std::string label = EntityRegistry::get_entities()[i]->name;
      label.append(" (" +
                   std::to_string(EntityRegistry::get_entities()[i]->get_id()) +
                   ")");
      if (ImGui::Button(label.c_str())) {
        selected_entity = EntityRegistry::get_entities()[i]->get_id();
      }
    }
    ImGui::End();

    ImGui::Begin("Inspector");
    if (selected_entity != -1) {
      Entity* e = EntityRegistry::get_entity_by_id(selected_entity);
      if (e) {
        ImGui::Text(("Entity ID: " + std::to_string(e->get_id())).c_str());
        ImGui::Text(("Name: " + e->name).c_str());

        ImGui::Separator();

        ImGui::Text("Transform");
        ImGui::DragFloat3("Position", &e->transform.position.x, 0.1f);
        ImGui::DragFloat3("Rotation", &e->transform.rotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &e->transform.scale.x, 0.1f, 0.01f, 100.0f);
      } else {
        selected_entity = -1;
      }
    } else {
      ImGui::Text("No entity selected.");
    }
    ImGui::End();

    window.set_title(std::to_string(Time::fps()));
    window.swap();
  }
}
