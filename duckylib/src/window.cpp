#include "../include/window.hpp"

using namespace ducky;
using namespace ducky::math;

Window::Window(const std::string& title, int w, int h) {
  SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;

  this->sdl_window_ =
      std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
          SDL_CreateWindow(title.c_str(), w, h, flags), SDL_DestroyWindow);

  if (this->sdl_window_.get() == nullptr) {
    RuntimeErr::throw_err("Failed to create SDL window: " +
                          std::string(SDL_GetError()));
    SDL_Quit();
  }

  this->sdl_glc_ = SDL_GL_CreateContext(this->sdl_window_.get());

  if (this->sdl_glc_ == nullptr) {
    RuntimeErr::throw_err("Failed to create OpenGL context: " +
                          std::string(SDL_GetError()));
    SDL_Quit();
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    RuntimeErr::throw_err("Failed to initialize GLAD");
    SDL_Quit();
  }

  this->running_ = true;
}

void Window::poll() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT)
      this->running_ = false;
  }
}

Vec2I Window::get_dimensions() {
  Vec2I d;
  SDL_GetWindowSize(this->sdl_window_.get(), &d.x, &d.y);

  return d;
}

float Window::get_viewport_aspect() const {
  return (float)this->viewport_size_.x / (float)this->viewport_size_.y;
}

void Window::render() {
  Vec2I viewport_pos;

  Vec2I dimensions = get_dimensions();

  float window_aspect = (float)dimensions.x / dimensions.y;
  float game_aspect = (float)1920 / 1080;

  this->pillarboxed_ = false;
  this->letterboxed_ = false;
  if (window_aspect > game_aspect) {
    this->viewport_size_.x = (int)(dimensions.y * game_aspect);
    this->viewport_size_.y = dimensions.y;

    viewport_pos.x = (dimensions.x - this->viewport_size_.x) / 2;
    viewport_pos.y = 0;
    this->pillarboxed_ = true;
  } else {
    this->viewport_size_.x = dimensions.x;
    this->viewport_size_.y = (int)(dimensions.x / game_aspect);
    viewport_pos.x = 0;
    viewport_pos.y = (dimensions.y - this->viewport_size_.y) / 2;
    this->letterboxed_ = true;
  }
  glViewport(viewport_pos.x, viewport_pos.y, this->viewport_size_.x,
             this->viewport_size_.y);
  SDL_GL_SwapWindow(this->sdl_window_.get());
}

bool Window::running() const { return running_; }

SDL_Window* Window::get() { return this->sdl_window_.get(); }