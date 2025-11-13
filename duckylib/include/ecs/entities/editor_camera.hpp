#pragma once

#include <algorithm>
#include "../../input/input.hpp"
#include "../../math/vec2.hpp"
#include "../../time.hpp"
#include "camera.hpp"

namespace ducky::ecs::entities {
class EditorCamera : public Camera {
 public:
  EditorCamera();
  void update() override;
  void imgui_widget() override;
  input::InputAxis axis_horizontal;
  input::InputAxis axis_forward;
  input::InputAxis axis_vertical;
  input::Keybind speed_up;
  input::Keybind slow_down;
  input::Keybind look;
  float sensitivity = 0.0005f;
  float speed = 0.01f;

 private:
  math::Vec2 last_mouse_;
  bool first_mouse_;
  bool can_move_;
  bool can_look_;
};
}  // namespace ducky::ecs::entities