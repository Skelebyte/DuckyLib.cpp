#pragma once

#include "keycode.hpp"

namespace ducky {

namespace input {

class Keybind {
 public:
  Keybind(Keycode code);
  Keycode keycode;
  bool pressed;
};

}  // namespace input

}  // namespace ducky