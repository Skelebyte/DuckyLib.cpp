#pragma once

#include <vector>
#include "../../third_party/glad/glad.h"
#include "../../third_party/ufbx/ufbx.h"
#include "../runtime_err.hpp"


namespace ducky::graphics {
class Mesh {
 public:
  Mesh(std::string path);
  std::vector<GLfloat> get_vertices() const;
  std::vector<GLuint> get_indices() const;

 private:
  std::vector<GLfloat> vertices_;
  std::vector<GLuint> indices_;
};
}  // namespace ducky::graphics