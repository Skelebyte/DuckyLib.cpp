#include "../../include/input/keybind.hpp"

using namespace ducky;
using namespace ducky::input;

Keybind::Keybind(Keycode code) {
  keycode = code;
  pressed = false;
}