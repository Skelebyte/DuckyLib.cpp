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
  static bool get_key(Keybind& keybind, bool once = false);
  static math::Vec2 get_mouse_position(Window& window, bool raw = false);
  static void cursor(Window& window, bool locked, bool hidden);
};

}  // namespace input

}  // namespace ducky