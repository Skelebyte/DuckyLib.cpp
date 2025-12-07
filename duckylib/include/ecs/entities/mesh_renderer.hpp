#pragma once

#include <iostream>
#include "../../../third_party/glad/glad.h"
#include "../../graphics/ebo.hpp"
#include "../../graphics/mesh.hpp"
#include "../../graphics/built_in_shapes.hpp"
#include "../../graphics/material.hpp"
#include "../../graphics/renderer.hpp"
#include "../../graphics/shader.hpp"
#include "../../graphics/vao.hpp"
#include "../../graphics/vbo.hpp"
#include "../../math/mat4.hpp"
#include "../../math/mathf.hpp"
#include "../../math/vec3.hpp"
#include "../../time.hpp"
#include "../../utils/serializable.hpp"
#include "../entity.hpp"
#include "../transform.hpp"
#include "camera.hpp"
#include "light.hpp"

namespace ducky {

namespace ecs {

namespace entities {

class MeshRenderer : public Entity {
 public:
  MeshRenderer(graphics::Mesh mesh = graphics::Mesh("assets/models/cube.fbx"),
               graphics::Material* material = new graphics::Material());
  ~MeshRenderer();
  void update() override;
  void imgui_widget() override;
  void save(std::string path) override;
  void load(std::string path) override;

  graphics::Material* material;

 private:
  size_t indices_size_;

  graphics::VAO vao_;
  graphics::VBO vbo_;
  graphics::EBO ebo_;

  math::Mat4 model_;
  GLuint model_uniform_;

  GLuint view_uniform_;
  GLuint projection_uniform_;

  GLuint scale_uniform_;
};

}  // namespace entities

}  // namespace ecs

}  // namespace ducky