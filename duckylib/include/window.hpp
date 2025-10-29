#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <iostream>
#include <memory>
#include "../third_party/glad/glad.h"
#include "graphics/renderer.hpp"
#include "math/vec2i.hpp"
#include "runtime_err.hpp"

namespace ducky {
class Window {
 public:
  Window(const std::string& title, int w, int h, bool init_renderer = true);
  void update();
  math::Vec2i get_dimensions();
  math::Vec2i get_viewport_size() const;
  math::Vec2i get_viewport_position() const;
  void stop();
  float get_viewport_aspect() const;
  void swap();
  bool running() const;
  SDL_Window* get();

 private:
  SDL_GLContext sdl_glc_;
  std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> sdl_window_ =
      nullptr;
  bool running_ = false;
  bool pillarboxed_;
  bool letterboxed_;
  math::Vec2i viewport_size_;
  math::Vec2i viewport_position_;
};
}  // namespace ducky