#include "../../include/graphics/renderer.hpp"
#include "../../include/graphics/shader.hpp"
#include "../ecs/entities/camera.hpp"
#include "../ecs/entities/light.hpp"

using namespace ducky;
using namespace ducky::math;
using namespace ducky::graphics;
using namespace ducky::ecs::entities;

bool Renderer::initialized_ = false;
bool Renderer::wireframe_ = false;
RendererSettings Renderer::settings_ = {};
std::vector<ducky::ecs::entities::PointLight*>
    ducky::graphics::Renderer::point_lights;
std::vector<ducky::ecs::entities::SpotLight*>
    ducky::graphics::Renderer::spot_lights;
std::vector<ducky::ecs::entities::DirectionalLight*>
    ducky::graphics::Renderer::directional_lights;

ducky::math::Vec3 ducky::graphics::Renderer::ambient_color =
    ducky::math::Vec3(0.1f, 0.1f, 0.1f);
float ducky::graphics::Renderer::ambient_strength = 0.2f;

void Renderer::init(RendererSettings renderer_settings) {
  if (initialized_) {
    std::cout << "Renderer is already initialized!\n";
    return;
  }
  if (renderer_settings.enable_blending) {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
  }

  if (renderer_settings.enable_depth_test) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }

  if (renderer_settings.enable_culling) {
    glEnable(GL_CULL_FACE);
    if (renderer_settings.culling_type == FaceCullingType::BACK) {
      glCullFace(GL_BACK);
    } else if (renderer_settings.culling_type ==
               FaceCullingType::FRONT) {  // super dooper coolio
      glCullFace(GL_FRONT);
    }
    glFrontFace(GL_CCW);
  }

  if (renderer_settings.enable_line_smoothing) {
    glEnable(GL_LINE_SMOOTH);
  }

  glEnable(GL_DITHER);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  settings_ = renderer_settings;
  initialized_ = true;
}

void Renderer::clear_frame(Color color) {
  if (!Time::should_render_frame())
    return;

  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int Renderer::get_max_point_lights() { return settings_.max_point_lights; }

int Renderer::get_max_spot_lights() { return settings_.max_spot_lights; }

int Renderer::get_max_directional_lights() {
  return settings_.max_directional_lights;
}

void Renderer::add_light(ecs::entities::Light* light) {
  if (light->get_type() == LightType::POINT) {
    if (point_lights.size() < settings_.max_point_lights) {
      point_lights.push_back((PointLight*)light);
    } else {
      std::cout << "Renderer::add_light: max point lights reached" << std::endl;
    }
  }

  if (light->get_type() == LightType::DIRECTIONAL) {
    if (directional_lights.size() < settings_.max_directional_lights) {
      directional_lights.push_back((DirectionalLight*)light);
    } else {
      std::cout << "Renderer::add_light: max directional lights reached"
                << std::endl;
    }
  }

  if (light->get_type() == LightType::SPOT) {
    std::cout << "Spotlight!\n";
    if (spot_lights.size() < settings_.max_spot_lights) {
      spot_lights.push_back((SpotLight*)light);
    } else {
      std::cout << "Renderer::add_light: max spot lights reached" << std::endl;
    }
  }
}

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

void Renderer::update_lights(Shader* shader, Camera* camera) {
  if (point_lights.size() > 0) {
#pragma region Point Lights
    glUniform1i(glGetUniformLocation(shader->id, "point_light_count"),
                (int)point_lights.size());
    Renderer::get_gl_error(
        "Renderer::update_lights - point_light_count uniform");

    glUniform3fv(glGetUniformLocation(shader->id, "camera_position"), 1,
                 camera->transform.position.data);
    Renderer::get_gl_error("Renderer::update_lights - camera_position uniform");

    for (size_t i = 0; i < point_lights.size(); i++) {
      std::string base = "point_lights[" + std::to_string(i) + "]";

      Vec3 color = Vec3(
          point_lights[i]->color.r, point_lights[i]->color.g,
          point_lights[i]->color.b);  // do this because point_lights[i]->color
                                      // is a Vec4, not a Vec3

      glUniform3fv(glGetUniformLocation(shader->id, (base + ".pos").c_str()), 1,
                   point_lights[i]->transform.position.data);
      Renderer::get_gl_error(
          "Renderer::update_lights - PointLight.pos uniform");

      glUniform3fv(glGetUniformLocation(shader->id, (base + ".color").c_str()),
                   1, color.data);
      Renderer::get_gl_error(
          "Renderer::update_lights - PointLight.color uniform");

      glUniform1fv(glGetUniformLocation(shader->id, (base + ".a").c_str()), 1,
                   &point_lights[i]->a);
      Renderer::get_gl_error("Renderer::update_lights - PointLight.a uniform");

      glUniform1fv(glGetUniformLocation(shader->id, (base + ".b").c_str()), 1,
                   &point_lights[i]->b);
      Renderer::get_gl_error("Renderer::update_lights - PointLight.b uniform");

      if (!point_lights[i]->enabled) {
        float zero = 0.0f;
        glUniform1fv(
            glGetUniformLocation(shader->id, (base + ".intensity").c_str()), 1,
            &zero);
        Renderer::get_gl_error(
            "Renderer::update_lights - PointLight.intensity uniform");
        glUniform3fv(
            glGetUniformLocation(shader->id, (base + ".color").c_str()), 1,
            Vec3(1.0f).data);
        Renderer::get_gl_error(
            "Renderer::update_lights - PointLight.color uniform");
      } else {
        glUniform1fv(
            glGetUniformLocation(shader->id, (base + ".intensity").c_str()), 1,
            &point_lights[i]->intensity);
        Renderer::get_gl_error(
            "Renderer::update_lights - PointLight.intensity uniform");
        glUniform3fv(
            glGetUniformLocation(shader->id, (base + ".color").c_str()), 1,
            color.data);
        Renderer::get_gl_error(
            "Renderer::update_lights - PointLight.color uniform");
      }
    }
#pragma endregion
  }

  if (spot_lights.size() > 0) {
#pragma region Spot Lights
    glUniform1i(glGetUniformLocation(shader->id, "spot_light_count"),
                (int)spot_lights.size());
    Renderer::get_gl_error(
        "Renderer::update_lights - spot_light_count uniform");

    glUniform3fv(glGetUniformLocation(shader->id, "camera_position"), 1,
                 camera->transform.position.data);
    Renderer::get_gl_error("Renderer::update_lights - camera_position uniform");

    for (size_t i = 0; i < spot_lights.size(); i++) {
      std::string base = "spot_lights[" + std::to_string(i) + "]";

      Vec3 color =
          Vec3(spot_lights[i]->color.r, spot_lights[i]->color.g,
               spot_lights[i]->color.b);  // do this because *_lights[i]->color
                                          // is a Vec4, not a Vec3

      glUniform3fv(glGetUniformLocation(shader->id, (base + ".pos").c_str()), 1,
                   spot_lights[i]->transform.position.data);
      Renderer::get_gl_error("Renderer::update_lights - SpotLight.pos uniform");

      glUniform1fv(glGetUniformLocation(shader->id,
                                        (base + ".outer_cone_angle").c_str()),
                   1, &spot_lights[i]->outer_cone);
      Renderer::get_gl_error(
          "Renderer::update_lights - SpotLight.outer_cone_angle uniform");

      glUniform1fv(glGetUniformLocation(shader->id,
                                        (base + ".inner_cone_angle").c_str()),
                   1, &spot_lights[i]->inner_cone);
      Renderer::get_gl_error(
          "Renderer::update_lights - SpotLight.inner_cone_angle uniform");

      if (!spot_lights[i]->enabled) {
        float zero = 0.0f;
        glUniform1fv(
            glGetUniformLocation(shader->id, (base + ".intensity").c_str()), 1,
            &zero);
        Renderer::get_gl_error(
            "Renderer::update_lights - SpotLight.intensity uniform");
        glUniform3fv(
            glGetUniformLocation(shader->id, (base + ".color").c_str()), 1,
            Vec3(1.0f).data);
        Renderer::get_gl_error(
            "Renderer::update_lights - SpotLight.color uniform");
      } else {
        glUniform1fv(
            glGetUniformLocation(shader->id, (base + ".intensity").c_str()), 1,
            &spot_lights[i]->intensity);
        Renderer::get_gl_error(
            "Renderer::update_lights - SpotLight.intensity uniform");
        glUniform3fv(
            glGetUniformLocation(shader->id, (base + ".color").c_str()), 1,
            color.data);
        Renderer::get_gl_error(
            "Renderer::update_lights - SpotLight.color uniform");
      }

      glUniform3fv(
          glGetUniformLocation(shader->id, (base + ".direction").c_str()), 1,
          spot_lights[i]->transform.rotation.data);
      Renderer::get_gl_error(
          "Renderer::update_lights - SpotLight.direction uniform");
    }
#pragma endregion
  }

  if (directional_lights.size() > 0) {
#pragma region Directional Lights
    glUniform1i(glGetUniformLocation(shader->id, "directional_light_count"),
                (int)directional_lights.size());
    Renderer::get_gl_error(
        "Renderer::update_lights - directional_light_count uniform");

    glUniform3fv(glGetUniformLocation(shader->id, "camera_position"), 1,
                 camera->transform.position.data);
    Renderer::get_gl_error("Renderer::update_lights - camera_position uniform");

    for (size_t i = 0; i < directional_lights.size(); i++) {
      std::string base = "directional_lights[" + std::to_string(i) + "]";

      Vec3 color =
          Vec3(directional_lights[i]->color.r, directional_lights[i]->color.g,
               directional_lights[i]
                   ->color.b);  // do this because *_lights[i]->color
                                // is a Vec4, not a Vec3

      glUniform3fv(glGetUniformLocation(shader->id, (base + ".pos").c_str()), 1,
                   directional_lights[i]->transform.position.data);
      Renderer::get_gl_error(
          "Renderer::update_lights - DirectionalLight.pos uniform");

      if (!directional_lights[i]->enabled) {
        float zero = 0.0f;
        glUniform1fv(
            glGetUniformLocation(shader->id, (base + ".intensity").c_str()), 1,
            &zero);
        Renderer::get_gl_error(
            "Renderer::update_lights - DirectionalLight.intensity uniform");
        glUniform3fv(
            glGetUniformLocation(shader->id, (base + ".color").c_str()), 1,
            Vec3(1.0f).data);
        Renderer::get_gl_error(
            "Renderer::update_lights - DirectionalLight.color uniform");
      } else {
        glUniform1fv(
            glGetUniformLocation(shader->id, (base + ".intensity").c_str()), 1,
            &directional_lights[i]->intensity);
        Renderer::get_gl_error(
            "Renderer::update_lights - DirectionalLight.intensity uniform");
        glUniform3fv(
            glGetUniformLocation(shader->id, (base + ".color").c_str()), 1,
            color.data);
        Renderer::get_gl_error(
            "Renderer::update_lights - DirectionalLight.color uniform");
      }

      glUniform3fv(
          glGetUniformLocation(shader->id, (base + ".direction").c_str()), 1,
          directional_lights[i]->transform.rotation.data);
      Renderer::get_gl_error(
          "Renderer::update_lights - DirectionalLight.direction uniform");
    }
#pragma endregion
  }
}

void Renderer::toggle_wireframe() {
  wireframe_ = !wireframe_;

  if (wireframe_) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}