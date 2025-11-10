#pragma once

#include <SDL3/SDL.h>
#include "../math/vec2.hpp"
#include "../window.hpp"
#include "input_axis.hpp"
#include "keybind.hpp"
#include "keycode.hpp"

namespace ducky {

namespace input {

class Input {
 public:
  static int get_axis(const InputAxis& axis);
  static bool get_key(Keybind* keybind);
  static bool get_key_once(Keybind* keybind);
  static math::Vec2 get_raw_mouse_position(Window& window);
  static math::Vec2 get_mouse_position(Window& window);
  static void cursor(Window& window, bool locked, bool hidden);

 private:
  static bool mouse_hidden_;
  static bool mouse_locked_;
};

}  // namespace input

}  // namespace ducky