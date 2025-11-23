#include <filesystem>
#define DUCKY_USE_NAMESPACES
#define DUCKY_ALLOW_ENGINE_KEYBINDS
#include "duckylib/ducky.hpp"

int main(int argc, char** argv) {
  App app(argv[1]);
  Window window("Ducky Editor", 1000, 800);

  Renderer::ambient_color = Vec3(1.0f);

  Renderer::main_shader = new Shader();

  Level current_level = Level("base_level");

  Renderer::main_camera = new EditorCamera();

  Text* text = new Text("Hello, Duckylib!");

  unsigned int selected_entity = -1;

  char name[128] = {};
  const char* types[] = {"MeshRenderer", "PointLight", "SpotLight",
                         "DirectionalLight"};
  int type_index = 0;
  bool spawn_zeroed = true;

  float font_size = 14.0f;
  char* font_path =
      (char*)"assets/fonts/Roboto_Mono/RobotoMono-VariableFont_wght.ttf";

  AudioPlayer* background_music =
      new AudioPlayer("assets/sounds/fanatica.wav", false, false);

  ImFont* font = window.io->Fonts->AddFontFromFileTTF(font_path, font_size);
  window.io->Fonts->Build();
  window.io->FontDefault = font;

  while (window.running()) {
    window.update();
    ducky_engine_keybinds();
    Renderer::clear_frame();
    EntityRegistry::update();

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
              cube_vertices, sizeof(cube_vertices), cube_indices,
              sizeof(cube_indices),
              new Material(new Texture(DEFAULT_TEXTURE),
                           new Texture(DEFAULT_TEXTURE), Color::white()));
          if (name != "") {
            new_entity->name = name;
          } else {
            new_entity->name = "mesh_renderer";
          }
        } else if (type_index == 1) {
          PointLight* new_entity = new PointLight();
          Renderer::add_light(new_entity);
          if (name != "") {
            new_entity->name = name;
          } else {
            new_entity->name = "point_light";
          }
        } else if (type_index == 2) {
          SpotLight* new_entity = new SpotLight();
          Renderer::add_light(new_entity);
          if (name != "") {
            new_entity->name = name;
          } else {
            new_entity->name = "spot_light";
          }
        } else if (type_index == 3) {
          DirectionalLight* new_entity = new DirectionalLight();
          Renderer::add_light(new_entity);
          if (name != "") {
            new_entity->name = name;
          } else {
            new_entity->name = "directional_light";
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
      char* name_temp = (char*)e->name.c_str();
      if (e) {
        ImGui::Checkbox("Enabled", &e->enabled);
        ImGui::Text(("Entity ID: " + std::to_string(e->get_id())).c_str());
        if (ImGui::InputText("Name", name_temp, 128)) {
          e->name = std::string(name_temp);
        }

        ImGui::Separator();

        e->imgui_widget();

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
    ImGui::Separator();
    ImGui::Text("Level Settings");
    char* level_name_temp = (char*)current_level.name.c_str();
    if (ImGui::InputText("Level Name", level_name_temp, 256)) {
      current_level.name = level_name_temp;
      current_level.update_paths();
    }
    if (ImGui::Button("Save Level")) {
      current_level.save(current_level.level_path);
    }
    if (ImGui::Button("Load Level")) {
      current_level.load(current_level.content_path);
    }
    if (ImGui::Button("Print Entities")) {
      for (Entity* e : EntityRegistry::get_entities()) {
        std::cout << "Entity: " << e->name << " (ID: " << e->get_id() << ")\n";
      }
    }
    if (ImGui::Button("leak memory")) {
      for (int i = 0; i < 100; i++) {
        if (i % 2 == 0) {
          current_level.name = "level_2";
          current_level.update_paths();
          current_level.load(current_level.content_path);
        } else {
          current_level.name = "level_1";
          current_level.update_paths();
          current_level.load(current_level.content_path);
        }
      }
    }

    ImGui::End();
    window.swap();
  }

  EntityRegistry::clear();
}
