#include "../include/window.hpp"

using namespace ducky;
using namespace ducky::math;
using namespace ducky::graphics;

Window::Window(const std::string& title, int w, int h, bool init_renderer) {
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

  if (init_renderer) {
    Renderer::init();
  }
}

void Window::update() {
  Time::begin_frame();
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT)
      this->running_ = false;
  }

  Vec2i dimensions = get_dimensions();

  float window_aspect = (float)dimensions.x / dimensions.y;
  float game_aspect = (float)1920 / 1080;

  this->pillarboxed_ = false;
  this->letterboxed_ = false;
  if (window_aspect > game_aspect) {
    this->viewport_size_.x = (int)(dimensions.y * game_aspect);
    this->viewport_size_.y = dimensions.y;

    this->viewport_position_.x = (dimensions.x - this->viewport_size_.x) / 2;
    this->viewport_position_.y = 0;
    this->pillarboxed_ = true;
  } else {
    this->viewport_size_.x = dimensions.x;
    this->viewport_size_.y = (int)(dimensions.x / game_aspect);
    this->viewport_position_.x = 0;
    this->viewport_position_.y = (dimensions.y - this->viewport_size_.y) / 2;
    this->letterboxed_ = true;
  }
  glViewport(this->viewport_position_.x, this->viewport_position_.y,
             this->viewport_size_.x, this->viewport_size_.y);
}

Vec2i Window::get_dimensions() {
  Vec2i d;
  SDL_GetWindowSize(this->sdl_window_.get(), &d.x, &d.y);

  return d;
}

Vec2i Window::get_viewport_size() const { return this->viewport_size_; }

Vec2i Window::get_viewport_position() const { return this->viewport_position_; }

void Window::stop() { this->running_ = false; }

float Window::get_viewport_aspect() const {
  return (float)this->viewport_size_.x / (float)this->viewport_size_.y;
}

void Window::swap() { SDL_GL_SwapWindow(this->sdl_window_.get()); }

bool Window::running() const { return running_; }

SDL_Window* Window::get() { return this->sdl_window_.get(); }

void Window::set_title(const std::string& title) {
  SDL_SetWindowTitle(sdl_window_.get(), title.c_str());
}