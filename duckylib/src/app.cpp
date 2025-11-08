#include "../include/app.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::entities;

App::App(const char* arg) {
  if (arg == "dev") {
    dev_mode_ = true;
  }

  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    RuntimeErr::throw_err("Failed to initialize SDL3: " +
                          std::string(SDL_GetError()));
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

  Time::set_target_fps(60);

  IMGUI_CHECKVERSION();
}

App::~App() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
  SDL_Quit();
}

// void App::dev_ui_update(Camera* camera, Shader* shader) {

//   if (!dev_mode_)
//     return;

//   ImGui::Begin("Entities");
//   if (ImGui::Button("Create Entity")) {
//     ImGui::OpenPopup("New Entity");
//   }

//   if (ImGui::BeginPopupModal("New Entity")) {
//     ImGui::InputText("Name", name, sizeof(name));
//     ImGui::Combo("Type", &type_index, types, IM_ARRAYSIZE(types));
//     ImGui::Checkbox("Spawn zeroed", &spawn_zeroed);
//     if (ImGui::Button("Create")) {
//       std::cout << "bogus!!!! " << type_index << "\n";
//       if (type_index == 0) {
//         MeshRenderer* new_entity = new MeshRenderer(
//             camera, cube_vertices, sizeof(cube_vertices), cube_indices,
//             sizeof(cube_indices), shader, &crate);
//         if (name != "") {
//           new_entity->name = name;
//         }
//       } else if (type_index == 1) {
//         PointLight* new_entity = new PointLight();
//         Renderer::add_light(new_entity);
//         if (name != "") {
//           new_entity->name = name;
//         }
//       } else if (type_index == 2) {
//         SpotLight* new_entity = new SpotLight();
//         Renderer::add_light(new_entity);
//         if (name != "") {
//           new_entity->name = name;
//         }
//       } else if (type_index == 3) {
//         DirectionalLight* new_entity = new DirectionalLight();
//         Renderer::add_light(new_entity);
//         if (name != "") {
//           new_entity->name = name;
//         }
//       }
//       std::cout << "closed\n";
//       ImGui::CloseCurrentPopup();
//     }
//     ImGui::EndPopup();
//   }

//   ImGui::Separator();

//   for (int i = 0; i < EntityRegistry::get_entities().size(); i++) {
//     std::string label = EntityRegistry::get_entities()[i]->name;
//     label.append(" (" +
//                  std::to_string(EntityRegistry::get_entities()[i]->get_id())
//                  +
//                  ")");
//     if (ImGui::Button(label.c_str())) {
//       selected_entity = EntityRegistry::get_entities()[i]->get_id();
//     }
//   }
//   ImGui::End();

//   ImGui::Begin("Inspector");
//   if (selected_entity != -1) {
//     Entity* e = EntityRegistry::get_entity_by_id(selected_entity);
//     if (e) {
//       ImGui::Checkbox("Enabled", &e->enabled);
//       ImGui::Text(("Entity ID: " + std::to_string(e->get_id())).c_str());
//       ImGui::Text(("Name: " + e->name).c_str());

//       ImGui::Separator();

//       ImGui::Text("Transform");
//       ImGui::DragFloat3("Position", e->transform.position.data, 0.1f);
//       ImGui::DragFloat3("Rotation", e->transform.rotation.data, 0.1f);
//       ImGui::DragFloat3("Scale", e->transform.scale.data, 0.1f, -100.0f,
//                         100.0f);
//     } else {
//       selected_entity = -1;
//     }
//   } else {
//     ImGui::Text("No entity selected.");
//   }
//   ImGui::End();

//   ImGui::Begin("Settings");
//   ImGui::Text(("FPS: " + std::to_string(Time::fps())).c_str());
//   int target_fps = Time::get_target_fps();
//   ImGui::DragInt("Target FPS", &target_fps, 1.0f, 1, 240);
//   Time::set_target_fps(target_fps);
//   ImGui::DragFloat("Time Scale", &Time::time_scale, 0.01f, 0.01f, 10.0f);
//   ImGui::ColorEdit3("Ambient Color", Renderer::ambient_color.data);
//   ImGui::End();
// }
