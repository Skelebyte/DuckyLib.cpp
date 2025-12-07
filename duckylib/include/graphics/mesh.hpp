#pragma once

#include <vector>
#include "../../third_party/glad/glad.h"
#include "../../third_party/ufbx/ufbx.h"
#include "../object.hpp"
#include "../runtime_err.hpp"


namespace ducky::graphics {
class Mesh {
 public:
  Mesh(GLfloat vertices[], GLuint indices[]);
  std::vector<GLfloat> get_vertices() const;
  std::vector<GLuint> get_indices() const;

  void load(std::string path);

 private:
  std::vector<GLfloat> vertices_;
  std::vector<GLuint> indices_;
};
}  // namespace ducky::graphics