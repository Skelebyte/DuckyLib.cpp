#include "../../../include/ecs/entities/mesh_renderer.hpp"

using namespace ducky;
using namespace ducky::graphics;
using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::math;
using namespace ducky::ecs::components;

MeshRenderer::MeshRenderer(Camera* camera, GLfloat vertices[],
                           size_t vertices_size, GLuint indices[],
                           size_t indices_size, Shader* shader,
                           Material material)
    : Entity("mesh_renderer") {
  this->camera_ = camera;

  this->indices_size_ = indices_size;

  this->shader_ = shader;

  this->vao_.init();
  this->vao_.bind();

  this->vbo_.init(vertices, vertices_size);
  this->ebo_.init(indices, indices_size);

  this->vao_.link_attribute(this->vbo_, 0, 3, GL_FLOAT, 8 * sizeof(float),
                            (void*)0);
  this->vao_.link_attribute(this->vbo_, 1, 2, GL_FLOAT, 8 * sizeof(float),
                            (void*)(3 * sizeof(float)));
  this->vao_.link_attribute(this->vbo_, 2, 3, GL_FLOAT, 8 * sizeof(float),
                            (void*)(5 * sizeof(float)));

  this->vao_.unbind();
  this->vbo_.unbind();
  this->ebo_.unbind();

  this->material_ = material;
  this->material_.get_uniforms(this->shader_);
  this->shader_->activate();
  this->material_.unbind();

  this->model_uniform_ = glGetUniformLocation(this->shader_->id, "model");
  this->view_uniform_ = glGetUniformLocation(this->shader_->id, "view");
  this->projection_uniform_ =
      glGetUniformLocation(this->shader_->id, "projection");
}

void MeshRenderer::update() {
  this->shader_->activate();

  this->model_ =
      Mat4::transformation(this->transform.position, this->transform.rotation,
                           this->transform.scale);

  glUniformMatrix4fv(this->model_uniform_, 1, GL_FALSE, this->model_.data);
  Renderer::get_gl_error("MeshRenderer::update - model uniform");
  glUniformMatrix4fv(this->view_uniform_, 1, GL_FALSE,
                     this->camera_->get_view().data);
  Renderer::get_gl_error("MeshRenderer::update - view uniform");

  glUniformMatrix4fv(this->projection_uniform_, 1, GL_FALSE,
                     this->camera_->get_projection().data);
  Renderer::get_gl_error("MeshRenderer::update - projection uniform");

  glUniform1i(glGetUniformLocation(this->shader_->id, "light_count"),
              (int)Renderer::lights.size());
  Renderer::get_gl_error("MeshRenderer::update - light_count uniform");

  glUniform3fv(glGetUniformLocation(this->shader_->id, "camera_position"), 1,
               this->camera_->transform.position.data);
  Renderer::get_gl_error("MeshRenderer::update - camera_position uniform");

  for (size_t i = 0; i < Renderer::lights.size(); i++) {
    std::string base = "lights[" + std::to_string(i) + "]";

    Vec3 color =
        Vec3(Renderer::lights[i]->color.r, Renderer::lights[i]->color.g,
             Renderer::lights[i]->color.b);

    glUniform3fv(
        glGetUniformLocation(this->shader_->id, (base + ".pos").c_str()), 1,
        Renderer::lights[i]->transform.position.data);
    Renderer::get_gl_error("MeshRenderer::update - light.pos uniform");

    glUniform3fv(
        glGetUniformLocation(this->shader_->id, (base + ".color").c_str()), 1,
        color.data);
    Renderer::get_gl_error("MeshRenderer::update - light.color uniform");
  }

  glUniform4fv(this->material_.color_uniform, 1, this->material_.color.data);
  Renderer::get_gl_error("MeshRenderer::update - setting color");

  glUniform1i(this->material_.diffuse_uniform, 0);
  Renderer::get_gl_error("MeshRenderer::update - setting diffuse");
  glUniform1i(this->material_.specular_uniform, 1);
  Renderer::get_gl_error("MeshRenderer::update - setting specular");

  glUniform1f(this->material_.specular_strength_uniform,
              this->material_.specular_strength);
  Renderer::get_gl_error("MeshRenderer::update - setting specular strength");

  this->material_.bind();
  Renderer::get_gl_error("MeshRenderer::update - material_.bind");
  this->vao_.bind();
  Renderer::get_gl_error("MeshRenderer::update - vao_.bind");
  glDrawElements(GL_TRIANGLES, this->indices_size_ / sizeof(int),
                 GL_UNSIGNED_INT, 0);
  Renderer::get_gl_error("MeshRenderer::update - glDrawElements");
}