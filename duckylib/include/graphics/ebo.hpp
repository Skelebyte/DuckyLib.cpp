#pragma once

#include "../../third_party/glad/glad.h"
#include "../object.hpp"

namespace ducky {

namespace graphics {

class EBO {
 public:
  EBO();
  ~EBO();
  void init(GLuint* indices, GLsizeiptr size);
  void bind();
  void unbind();
  GLuint id;
};

}  // namespace graphics

}  // namespace ducky