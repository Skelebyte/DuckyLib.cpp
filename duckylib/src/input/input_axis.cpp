#include "../../include/input/input_axis.hpp"

using namespace ducky;
using namespace ducky::input;

InputAxis::InputAxis(Keycode pos, Keycode neg) {
  this->positive = pos;
  this->negative = neg;
}