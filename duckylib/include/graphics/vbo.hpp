#pragma once

#include "../../third_party/glad/glad.h"

namespace ducky {

namespace graphics {

class VBO {
 public:
  VBO(GLfloat* vertices, GLsizeiptr size);
  ~VBO();
  void bind();
  void unbind();
  void destroy();
  GLuint id;
};

}  // namespace graphics

}  // namespace ducky