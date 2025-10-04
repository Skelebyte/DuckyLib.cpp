#pragma once

#include "../../third_party/glad/glad.h"

namespace ducky {

namespace graphics {

class VBO {
 public:
  ~VBO();
  void init(GLfloat* vertices, GLsizeiptr size);
  void bind();
  void unbind();
  void destroy();
  GLuint id;
};

}  // namespace graphics

}  // namespace ducky