#pragma once

#include "../../third_party/glad/glad.h"
#include "../object.hpp"

namespace ducky {

namespace graphics {

class EBO : public Object {
 public:
  EBO();
  void init(GLuint* indices, GLsizeiptr size);
  ~EBO();
  void bind();
  void unbind();
  void destroy();
  GLuint id;
};

}  // namespace graphics

}  // namespace ducky