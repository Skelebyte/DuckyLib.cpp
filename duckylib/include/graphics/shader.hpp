#pragma once

#include <iostream>
#include "../../third_party/glad/glad.h"
#include "../utils/file.hpp"
#include "built_in_shaders.hpp"
#include "renderer.hpp"

namespace ducky {

namespace graphics {

class Shader {
 public:
  Shader();
  Shader(std::string vert_path, std::string frag_path);
  ~Shader();
  void activate();
  void destroy();
  void check_compile(GLuint shader, std::string type);
  void check_link();
  GLuint id;
};

}  // namespace graphics

}  // namespace ducky