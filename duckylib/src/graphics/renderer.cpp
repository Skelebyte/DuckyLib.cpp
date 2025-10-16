#include "../../include/graphics/renderer.hpp"
#include "../ecs/entities/light.hpp"

using namespace ducky;
using namespace ducky::graphics;

int Renderer::max_lights_ = 0;
std::vector<ducky::ecs::entities::Light*> ducky::graphics::Renderer::lights;

void Renderer::init(int max_lights) {
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  glEnable(GL_LINE_SMOOTH);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  max_lights_ = max_lights;
}

void Renderer::clear_frame(Color color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int Renderer::get_max_lights() { return max_lights_; }

void Renderer::add_light(ecs::entities::Light* light) {
  if (lights.size() < max_lights_) {
    lights.push_back(light);
  } else {
    std::cout << "Renderer::add_light: max lights reached" << std::endl;
  }
}

void Renderer::update_lights() {}

void Renderer::get_gl_error(std::string error_context) {
  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    if (error_context != "")
      RuntimeErr::throw_err("OpenGL error in " + error_context + ": " +
                            std::to_string(err));
    else {
      RuntimeErr::throw_err("OpenGL error: " + std::to_string(err));
    }
  }
}