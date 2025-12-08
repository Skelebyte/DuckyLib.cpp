#include "../include/editor.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::ecs::entities::ui;
using namespace ducky::graphics;
using namespace ducky::math;
using namespace ducky::input;
using namespace ducky::tools;
using namespace ducky::utils;

unsigned int ducky::Editor::selected_entity = -1;
char ducky::Editor::entity_name_[128] = {"new_entity"};
const char* ducky::Editor::entity_types_[6] = {
    "MeshRenderer",     "PointLight",  "SpotLight",
    "DirectionalLight", "AudioPlayer", "UI Text"};
int ducky::Editor::type_index_ = 0;

void ducky::Editor::update(Level& current_level) {
  ImGui::Begin("Entities");
  if (ImGui::Button("Create Entity")) {
    ImGui::OpenPopup("New Entity");
  }

  if (ImGui::BeginPopupModal("New Entity")) {
    ImGui::InputText("Name", entity_name_, sizeof(entity_name_));
    ImGui::Combo("Type", &type_index_, entity_types_,
                 IM_ARRAYSIZE(entity_types_));
    if (ImGui::Button("Create")) {
      if (type_index_ == 0) {
        MeshRenderer* new_entity = new MeshRenderer(
            Mesh("assets/models/tent.dmdl"),
            new Material(
                new Texture("assets/textures/frank.png", Blendmode::NEAREST),
                new Texture(DEFAULT_TEXTURE, Blendmode::NEAREST),
                Color::white()));
        if (entity_name_ != "") {
          new_entity->name = entity_name_;
        } else {
          new_entity->name = "mesh_renderer";
        }
      } else if (type_index_ == 1) {
        PointLight* new_entity = new PointLight();
        Renderer::add_light(new_entity);
        if (entity_name_ != "") {
          new_entity->name = entity_name_;
        } else {
          new_entity->name = "point_light";
        }
      } else if (type_index_ == 2) {
        SpotLight* new_entity = new SpotLight();
        Renderer::add_light(new_entity);
        if (entity_name_ != "") {
          new_entity->name = entity_name_;
        } else {
          new_entity->name = "spot_light";
        }
      } else if (type_index_ == 3) {
        DirectionalLight* new_entity = new DirectionalLight();
        Renderer::add_light(new_entity);
        if (entity_name_ != "") {
          new_entity->name = entity_name_;
        } else {
          new_entity->name = "directional_light";
        }
      } else if (type_index_ == 4) {
        AudioPlayer* new_entity = new AudioPlayer();
        if (entity_name_ != "") {
          new_entity->name = entity_name_;
        } else {
          new_entity->name = "audio_player";
        }
      } else if (type_index_ == 5) {
        Text* new_entity = new Text();
        if (entity_name_ != "") {
          new_entity->name = entity_name_;
        } else {
          new_entity->name = "ui_text";
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
    label.append(
        " (id: " + std::to_string(EntityRegistry::get_entities()[i]->get_id()) +
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
      if (ImGui::InputText("Name", name_temp, 256)) {
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
  ImGui::End();
}