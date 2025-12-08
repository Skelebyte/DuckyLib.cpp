#include "../../../../include/ecs/entities/ui/text.hpp"

using namespace ducky;
using namespace ducky::math;
using namespace ducky::graphics;
using namespace ducky::ecs;
using namespace ducky::tools;
using namespace ducky::ecs::entities::ui;

Text::Text(std::string content) : Entity("ui_text", "ui_text") {
  type_ = EntityType::UI_TEXT;

  this->content = content;
}

Text::~Text() {}

void Text::update() {
  transform.process();
  if (font_path == "" || AssetManager::is_path_valid(font_path) == false) {
    return;
  }
}

void Text::imgui_widget() {
  transform.imgui_widget();
  if (!ImGui::CollapsingHeader("UI Text")) {
    return;
  }

  ImGui::InputText("Font Path", (char*)font_path.c_str(), 256);

  char* content_temp = (char*)content.c_str();
  if (ImGui::InputText("Content", content_temp, 256)) {
    content = std::string(content_temp);
  }
  ImGui::DragFloat("Font Size", &font_size, 1.0f, 8.0f, 72.0f);
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

void Text::apply_font() {
  FILE* font_file = fopen(font_path.c_str(), "rb");
  fseek(font_file, 0, SEEK_END);
  size_t font_size_t = ftell(font_file);
  fseek(font_file, 0, SEEK_SET);

  unsigned char* font_buffer = new unsigned char[font_size_t];

  fread(font_buffer, font_size_t, 1, font_file);
  fclose(font_file);

  // stbtt_fontinfo font_info;
  // if (!stbtt_InitFont(&font_info, font_buffer, 0)) {
  //   RuntimeErr::throw_err("Failed to initialize font: " + font_path);
  // }
}