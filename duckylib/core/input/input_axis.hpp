#pragma once

#include "keycode.hpp"

namespace ducky {

namespace input {

class InputAxis {
 public:
  InputAxis(Keycode pos, Keycode neg);
  Keycode positive;
  Keycode negative;
};

}  // namespace input

}  // namespace ducky