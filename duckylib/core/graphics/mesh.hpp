#pragma once

#include <vector>
#include "../../third_party/glad/glad.h"

namespace ducky::graphics {
class Mesh {
 public:
  Mesh(GLfloat vertices[], GLuint indices[]);
  std::vector<GLfloat> get_vertices() const;
  std::vector<GLuint> get_indices() const;

 private:
  std::vector<GLfloat> vertices_;
  std::vector<GLuint> indices_;
};
}  // namespace ducky::graphics