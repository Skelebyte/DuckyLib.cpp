#pragma once

#include <iostream>
// #define STB_TRUETYPE_IMPLEMENTATION
// #include "../../../../third_party/stb/stb_truetype.h"
#include "../../../graphics/color.hpp"
#include "../../../graphics/renderer.hpp"
#include "../../../math/vec2i.hpp"
#include "../../../tools/asset_manager.hpp"
#include "../../../window.hpp"
#include "../../entity.hpp"

namespace ducky::ecs::entities::ui {
class Text : public Entity {
 public:
  Text(std::string content = "Text");
  ~Text();
  void update() override;
  void imgui_widget() override;
  void save(std::string path) override;
  void load(std::string path) override;
  std::string content;
  std::string font_path;
  graphics::Color color = graphics::Color::white();
  float font_size = 16.0f;

 protected:
  void apply_font();
};

}  // namespace ducky::ecs::entities::ui