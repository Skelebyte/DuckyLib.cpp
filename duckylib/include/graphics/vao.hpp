#pragma once

#include "../../third_party/glad/glad.h"
#include "vbo.hpp"

namespace ducky {

namespace graphics {

class VAO {
 public:
  VAO();
  ~VAO();
  void link_attribute(VBO& vbo, GLuint layout, GLuint num_components,
                      GLenum type, GLsizeiptr stride, void* offset);
  void bind();
  void unbind();
  void destroy();
  GLuint id;
};

}  // namespace graphics

}  // namespace ducky