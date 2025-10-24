#pragma once

#include "../../third_party/glad/glad.h"

namespace ducky {

namespace graphics {

class EBO {
 public:
  void init(GLuint* indices, GLsizeiptr size);
  ~EBO();
  void bind();
  void unbind();
  void destroy();
  GLuint id;
};

}  // namespace graphics

}  // namespace ducky