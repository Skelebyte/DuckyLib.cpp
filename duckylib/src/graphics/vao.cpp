#include "../../include/graphics/vao.hpp"

using namespace ducky;
using namespace ducky::graphics;

void VAO::init() { glGenVertexArrays(1, &this->id); }

VAO::~VAO() { this->destroy(); }

void VAO::link_attribute(VBO& vbo, GLuint layout, GLuint num_components,
                         GLenum type, GLsizeiptr stride, void* offset) {
  vbo.bind();
  glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  vbo.unbind();
}

void VAO::bind() { glBindVertexArray(this->id); }

void VAO::unbind() { glBindVertexArray(0); }

void VAO::destroy() { glDeleteVertexArrays(1, &this->id); }