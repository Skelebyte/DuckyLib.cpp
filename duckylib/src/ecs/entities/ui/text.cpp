#include "../../../../include/ecs/entities/ui/text.hpp"

using namespace ducky;
using namespace ducky::math;
using namespace ducky::graphics;
using namespace ducky::ecs;
using namespace ducky::ecs::entities::ui;

Text::Text(std::string content) : Entity("ui_text", "ui_text") {
  type_ = EntityType::UI_TEXT;

  this->content = content;
}

Text::~Text() {}

void Text::update() {
  transform.process();
  Vec2i center;
  center.x = (Renderer::main_window->get_viewport_size().x / 2) +
             Renderer::main_window->get_viewport_position().x +
             transform.position.x;
  center.y = (Renderer::main_window->get_viewport_size().y / 2) +
             Renderer::main_window->get_viewport_position().y +
             transform.position.y;
  ImGui::Begin("Text", nullptr, overlay_flags_);
  ImGuiStyle& style = ImGui::GetStyle();
  style.Colors[ImGuiCol_Text] = ImVec4(color.r, color.g, color.b, color.a);
  ImGui::Text(content.c_str());
  style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
  ImGui::SetWindowPos(ImVec2(center.x, center.y), ImGuiCond_Always);
  ImGui::End();
}

void Text::imgui_widget() {
  transform.imgui_widget();
  ImGui::Text("UI Text");

  char* content_temp = (char*)content.c_str();
  if (ImGui::InputText("Content", content_temp, 256)) {
    content = std::string(content_temp);
  }
  ImGui::ColorEdit4("Font Color", color.data);
}

void Text::save(std::string path) {
  add_entity_data();

  add("content", content, "ui_text");

  write(path);
}

void Text::load(std::string path) {
  load_entity_data(path);

  content = get(path, "content", "ui_text");
}