#pragma once

#include <iostream>
#include "../../third_party/glad/glad.h"
#include "../utils/file.hpp"
#include "built_in_shaders.hpp"

namespace ducky {

namespace graphics {

class Shader {
 public:
  Shader();
  Shader(std::string vert_path, std::string frag_path);
  ~Shader();
  void activate();
  void destroy();
  GLuint id;
};

}  // namespace graphics

}  // namespace ducky