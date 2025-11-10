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

  Renderer::ambient_color = Vec3(1.0f);

  Shader shader;
  EditorCamera camera(&window);
  camera.transform.position = Vec3(-3, 0, 4);

  Material crate(Texture("assets/textures/container_diffuse.png"),
                 Texture("assets/textures/container_specular.png"),
                 Color::white());
  crate.specular_strength = 1.0f;

  Material bird(Texture("assets/textures/damn.png"), Texture(DEFAULT_TEXTURE),
                Color::white());
  bird.specular_strength = 1.0f;

  MeshRenderer cube(&camera, cube_vertices, sizeof(cube_vertices), cube_indices,
                    sizeof(cube_indices), &shader, &crate);

  MeshRenderer damn(&camera, plane_vertices, sizeof(plane_vertices),
                    plane_indices, sizeof(plane_indices), &shader, &bird);
  damn.name = "DAMN!!!";

  DirectionalLight sun;
  sun.transform.rotation = Vec3(1.0f);
  sun.color = Color(0.98f, 0.94f, 0.8f, 1.0f);
  Renderer::add_light(&sun);

  unsigned int selected_entity = -1;

  char name[128] = {};
  const char* types[] = {"MeshRenderer", "PointLight", "SpotLight",
                         "DirectionalLight"};
  int type_index = 0;
  bool spawn_zeroed = true;

  while (window.running()) {
    window.update();
    ducky_engine_keybinds();
    Renderer::clear_frame();
    EntityRegistry::update();

    ImFont* font = window.io->Fonts->AddFontFromFileTTF(
        "assets/fonts/Roboto_Mono/RobotoMono-Italic-VariableFont_wght.ttf",
        32.0f);
    window.io->Fonts->Build();
    window.io->FontDefault = font;
    ImGui::Begin("Entities");
    if (ImGui::Button("Create Entity")) {
      ImGui::OpenPopup("New Entity");
    }

    if (ImGui::BeginPopupModal("New Entity")) {
      ImGui::InputText("Name", name, sizeof(name));
      ImGui::Combo("Type", &type_index, types, IM_ARRAYSIZE(types));
      ImGui::Checkbox("Spawn zeroed", &spawn_zeroed);
      if (ImGui::Button("Create")) {
        if (type_index == 0) {
          MeshRenderer* new_entity = new MeshRenderer(
              &camera, cube_vertices, sizeof(cube_vertices), cube_indices,
              sizeof(cube_indices), &shader, &crate);
          if (name != "") {
            new_entity->name = name;
          }
        } else if (type_index == 1) {
          PointLight* new_entity = new PointLight();
          Renderer::add_light(new_entity);
          if (name != "") {
            new_entity->name = name;
          }
        } else if (type_index == 2) {
          SpotLight* new_entity = new SpotLight();
          Renderer::add_light(new_entity);
          if (name != "") {
            new_entity->name = name;
          }
        } else if (type_index == 3) {
          DirectionalLight* new_entity = new DirectionalLight();
          Renderer::add_light(new_entity);
          if (name != "") {
            new_entity->name = name;
          }
        }
        std::cout << "closed\n";
        ImGui::CloseCurrentPopup();
      }
      ImGui::Separator();
      if (ImGui::Button("Cancel")) {
        ImGui::CloseCurrentPopup();
      }
      ImGui::EndPopup();
    }

    ImGui::Separator();

    for (int i = 0; i < EntityRegistry::get_entities().size(); i++) {
      std::string label = EntityRegistry::get_entities()[i]->name;
      label.append(" (id: " +
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
        ImGui::Checkbox("Enabled", &e->enabled);
        ImGui::Text(("Entity ID: " + std::to_string(e->get_id())).c_str());
        ImGui::Text(("Name: " + e->name).c_str());

        ImGui::Separator();

        ImGui::Text("Transform");
        ImGui::DragFloat3("Position", e->transform.position.data, 0.1f);
        ImGui::DragFloat3("Rotation", e->transform.rotation.data, 0.1f);
        ImGui::DragFloat3("Scale", e->transform.scale.data, 0.1f, -100.0f,
                          100.0f);
      } else {
        selected_entity = -1;
      }
    } else {
      ImGui::Text("No entity selected.");
    }
    ImGui::End();

    ImGui::Begin("Settings");
    ImGui::Text(("FPS: " + std::to_string(Time::fps())).c_str());
    int target_fps = Time::get_target_fps();
    ImGui::DragInt("Target FPS", &target_fps, 1.0f, 1, 240);
    Time::set_target_fps(target_fps);
    ImGui::DragFloat("Time Scale", &Time::time_scale, 0.01f, 0.01f, 10.0f);
    ImGui::ColorEdit3("Ambient Color", Renderer::ambient_color.data);
    ImGui::ColorEdit3("Sun Color", sun.color.data);

    ImGui::Spacing();

    ImGui::Text("Controls");
    ImGui::Separator();
    ImGui::Text("WASD - Move camera");
    ImGui::Text("Right Mouse Button - Look");
    ImGui::Text("Left Shift - Speed up");
    ImGui::Text("Left Control - Slow down");
    ImGui::DragFloat("Sensitivity", &camera.sensitivity, 0.0001f, 0.0001f,
                     0.01f);
    ImGui::DragFloat("Speed", &camera.speed, 0.001f, 0.001f, 100.0f);
    ImGui::End();

    ImGui::ShowDemoWindow();

    ImGuiWindowFlags overlay_flags = ImGuiWindowFlags_NoDecoration |
                                     ImGuiWindowFlags_NoResize |
                                     ImGuiWindowFlags_NoBackground;

    bool overlay_open = true;

    ImGui::Begin("Overlay!", &overlay_open, overlay_flags);
    ImGui::Text("This is an overlay!");
    ImGui::End();

    window.set_title(std::to_string(Time::fps()));
    window.swap();
  }
}
