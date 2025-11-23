#include <iostream>
#include "../../../../third_party/imgui/imgui.h"
#include "../../../graphics/renderer.hpp"
#include "../../../math/vec2i.hpp"
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

 private:
  char buffer_[256] = "";
  ImGuiWindowFlags overlay_flags_ =
      ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;
};

}  // namespace ducky::ecs::entities::ui