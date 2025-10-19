#include "../../include/graphics/renderer.hpp"
#include "../ecs/entities/light.hpp"

using namespace ducky;
using namespace ducky::graphics;

bool Renderer::initialized_ = false;
RendererSettings Renderer::settings_ = {};
std::vector<ducky::ecs::entities::Light*> ducky::graphics::Renderer::lights;

void Renderer::init(RendererSettings renderer_settings) {
  if(initialized_) {
    std::cout<<"Renderer is already initialized!\n";
    return;
  }
  if(renderer_settings.enable_blending) {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
  }

  if(renderer_settings.enable_depth_test) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }

  if(renderer_settings.enable_culling) {
    glEnable(GL_CULL_FACE);
    if(renderer_settings.culling_type == FaceCullingType::BACK) {
      glCullFace(GL_BACK);
    } else if(renderer_settings.culling_type == FaceCullingType::FRONT) {// super dooper coolio
      glCullFace(GL_FRONT);
    }
    glFrontFace(GL_CCW);
  }

  if(renderer_settings.enable_line_smoothing) {
    glEnable(GL_LINE_SMOOTH);
  }


  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  settings_ = renderer_settings;
  initialized_ = true;
}

void Renderer::clear_frame(Color color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int Renderer::get_max_lights() { return settings_.max_lights; }

void Renderer::add_light(ecs::entities::Light* light) {
  if (lights.size() < settings_.max_lights) {
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