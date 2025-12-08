#pragma once

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include "../../third_party/glad/glad.h"
#include "../../third_party/ufbx/ufbx.h"
#include "../math/vec2.hpp"
#include "../math/vec3.hpp"
#include "../runtime_err.hpp"
#include "../utils/file.hpp"

namespace ducky::graphics {
class Mesh {
 public:
  Mesh(std::string path);
  std::vector<GLfloat> get_vertices() const;
  std::vector<GLuint> get_indices() const;
  int get_vertices_length() const;
  int get_indices_length() const;

 private:
  std::vector<GLfloat> vertices_;
  std::vector<GLuint> indices_;
  int vertices_length_;
  int indices_length_;
};
}  // namespace ducky::graphics