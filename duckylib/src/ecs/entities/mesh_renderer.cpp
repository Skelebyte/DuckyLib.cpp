#include "../../../include/ecs/entities/mesh_renderer.hpp"

using namespace ducky;
using namespace ducky::graphics;
using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::math;
using namespace ducky::ecs::components;

MeshRenderer::MeshRenderer(Camera* camera, GLfloat vertices[],
                           size_t vertices_size, GLuint indices[],
                           size_t indices_size, graphics::Shader* shader,
                           graphics::Texture texture)
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

  this->texture_ = texture;
  this->texture_uniform_ = glGetUniformLocation(this->shader_->id, "tex0");
  this->shader_->activate();
  this->texture_.unbind();

  this->model_uniform_ = glGetUniformLocation(this->shader_->id, "model");
  this->view_uniform_ = glGetUniformLocation(this->shader_->id, "view");
  this->projection_uniform_ =
      glGetUniformLocation(this->shader_->id, "projection");
}

void MeshRenderer::set_texture(graphics::Texture new_texture) {
  this->texture_ = new_texture;
  this->texture_uniform_ = glGetUniformLocation(this->shader_->id, "tex0");
  this->shader_->activate();
  this->texture_.unbind();
}

void MeshRenderer::update() {
  this->shader_->activate();

  this->model_ =
      Mat4::transformation(this->transform.position, this->transform.rotation,
                           this->transform.scale);

  glUniformMatrix4fv(this->model_uniform_, 1, GL_FALSE, this->model_.data);
  glUniformMatrix4fv(this->view_uniform_, 1, GL_FALSE,
                     this->camera_->get_view().data);

  glUniformMatrix4fv(this->projection_uniform_, 1, GL_FALSE,
                     this->camera_->get_projection().data);

  glUniform1i(glGetUniformLocation(this->shader_->id, "light_count"),
              (int)Renderer::lights.size());

  glUniform3fv(glGetUniformLocation(this->shader_->id, "camera_position"), 1,
               this->camera_->transform.position.data);

  for (size_t i = 0; i < Renderer::lights.size(); i++) {
    std::string base = "lights[" + std::to_string(i) + "]";

    Vec3 color =
        Vec3(Renderer::lights[i]->color.r, Renderer::lights[i]->color.g,
             Renderer::lights[i]->color.b);

    glUniform3fv(
        glGetUniformLocation(this->shader_->id, (base + ".pos").c_str()), 1,
        Renderer::lights[i]->transform.position.data);

    glUniform3fv(
        glGetUniformLocation(this->shader_->id, (base + ".color").c_str()), 1,
        color.data);

    int light_pos_loc =
        glGetUniformLocation(this->shader_->id, "lights[0].pos");
    int light_color_loc =
        glGetUniformLocation(this->shader_->id, "lights[0].color");
  }
  this->texture_.bind();
  this->vao_.bind();
  glDrawElements(GL_TRIANGLES, this->indices_size_ / sizeof(int),
                 GL_UNSIGNED_INT, 0);
}