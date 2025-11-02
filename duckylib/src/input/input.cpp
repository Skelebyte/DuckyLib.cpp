#include "../../include/input/input.hpp"

using namespace ducky;
using namespace ducky::math;
using namespace ducky::input;

int Input::get_axis(const InputAxis& axis) {
  SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);

  if (axis.positive < 0 && axis.negative < 0) {
    if (flags & SDL_BUTTON_MASK(-axis.positive) &&
        flags & SDL_BUTTON_MASK(-axis.negative)) {
      return 0;
    }
  }

  if (axis.positive < 0) {
    if (flags == SDL_BUTTON_MASK(-axis.positive)) {
      return 1;
    }
  }

  if (axis.negative < 0) {
    if (flags == SDL_BUTTON_MASK(-axis.negative)) {
      return -1;
    }
  }

  const bool* input = SDL_GetKeyboardState(NULL);
  if (input[axis.positive] == true && input[axis.negative] == true) {
    return 0;
  }

  if (input[axis.positive] == true) {
    return 1;
  }

  if (input[axis.negative] == true) {
    return -1;
  }

  return 0;
}

bool Input::get_key(Keybind* keybind, bool once) {
  SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);

  if (keybind->keycode < 0) {  // checking mouse keys
    if (once == true) {
      if (flags & SDL_BUTTON_MASK(-keybind->keycode) &&
          keybind->pressed == false) {
        keybind->pressed = true;
        return true;
      }

      if ((flags & SDL_BUTTON_MASK(-keybind->keycode)) == 0 &&
          keybind->pressed == true) {
        keybind->pressed = false;
        return false;
      }

      if (once) {
        std::cout << keybind->keycode << ", " << keybind->pressed << std::endl;
      }

    } else {
      if (flags == SDL_BUTTON_MASK(-keybind->keycode)) {
        keybind->pressed = true;
        return true;
      } else {
        keybind->pressed = false;
        return false;
      }
    }

    return false;
  }

  const bool* input = SDL_GetKeyboardState(NULL);
  if (once == true)  // get key after its been pressed once
  {
    if (input[keybind->keycode] == true && keybind->pressed == false) {
      keybind->pressed = true;
      return true;
    }

    if (input[keybind->keycode] == false && keybind->pressed == true) {
      keybind->pressed = false;
      return false;
    }
  } else  // get key while its down
  {
    if (input[keybind->keycode] == true) {
      keybind->pressed = true;
      return true;
    } else {
      keybind->pressed = false;
      return false;
    }
  }

  return false;
}

math::Vec2 Input::get_mouse_position(Window& window, bool raw) {
  Vec2 pos;
  SDL_GetMouseState(&pos.x, &pos.y);

  if (raw) {
    return pos;
  } else {
    pos.x -= window.get_viewport_position().x;
    pos.x -= window.get_viewport_size().x / 2;
    pos.x /= window.get_viewport_size().x / 2;
    pos.y -= window.get_viewport_position().y;
    pos.y -= window.get_viewport_size().y / 2;
    pos.y /= window.get_viewport_size().y / 2;

    pos.y = -pos.y;

    if (pos.x > 1.0f)
      pos.x = 1.0f;
    if (pos.x < -1.0f)
      pos.x = -1.0f;
    if (pos.y > 1.0f)
      pos.y = 1.0f;
    if (pos.y < -1.0f)
      pos.y = -1.0f;

    return pos;
  }
}

void Input::cursor(Window& window, bool locked, bool hidden) {
  if (locked) {
    // SDL_WarpMouseInWindow(window.get(), window.get_dimensions().x / 2,
    //                       window.get_dimensions().y / 2);
  }
  // SDL_SetWindowMouseGrab(window.get(), locked);

  SDL_SetWindowRelativeMouseMode(window.get(), locked);

  if (hidden) {
    SDL_HideCursor();
  } else {
    SDL_ShowCursor();
  }
}