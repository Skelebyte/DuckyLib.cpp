#include "../../include/graphics/shader.hpp"

using namespace ducky;
using namespace ducky::graphics;

Shader::Shader() {
  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &vertex_shader_src, NULL);
  glCompileShader(vert_shader);

  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &fragment_shader_src, NULL);
  glCompileShader(frag_shader);

  this->id = glCreateProgram();

  glAttachShader(this->id, vert_shader);
  glAttachShader(this->id, frag_shader);
  glLinkProgram(this->id);

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);
}

Shader::Shader(std::string vert_path, std::string frag_path) {
  std::string vert_str = File::read(vert_path);
  std::string frag_str = File::read(frag_path);

  const char* vert = vert_str.c_str();

  const char* frag = frag_str.c_str();

  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &vert, NULL);
  glCompileShader(vert_shader);

  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &frag, NULL);
  glCompileShader(frag_shader);

  this->id = glCreateProgram();

  glAttachShader(this->id, vert_shader);
  glAttachShader(this->id, frag_shader);
  glLinkProgram(this->id);

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);
}

Shader::~Shader() { this->destroy(); }

void Shader::activate() { glUseProgram(this->id); }

void Shader::destroy() { glDeleteProgram(this->id); }
