#pragma once

#include <iostream>
#include "../../../third_party/glad/glad.h"
#include "../../graphics/ebo.hpp"
#include "../../graphics/shader.hpp"
#include "../../graphics/texture.hpp"
#include "../../graphics/vao.hpp"
#include "../../graphics/vbo.hpp"
#include "../../math/mat4.hpp"
#include "../../math/mathf.hpp"
#include "../../math/vec3.hpp"
#include "../components/transform.hpp"
#include "../entity.hpp"
#include "camera.hpp"
#include "light.hpp"

namespace ducky {

namespace ecs {

namespace entities {

class MeshRenderer : public Entity {
 public:
  MeshRenderer(Camera* camera, GLfloat vertices[], size_t vertices_size,
               GLuint indices[], size_t indices_size,
               graphics::Shader* shader =
                   new graphics::Shader("assets/shaders/vertex.glsl",
                                        "assets/shaders/fragment.glsl"),
               graphics::Texture texture = graphics::Texture());
  void set_texture(graphics::Texture new_texture);
  void update() override;
  graphics::Shader* shader_;

 private:
  Camera* camera_;

  size_t indices_size_;

  graphics::VAO vao_;
  graphics::VBO vbo_;
  graphics::EBO ebo_;

  graphics::Texture texture_;
  GLuint texture_uniform_;

  math::Mat4 model_;
  GLuint model_uniform_;

  GLuint view_uniform_;
  GLuint projection_uniform_;
};

}  // namespace entities

}  // namespace ecs

}  // namespace ducky