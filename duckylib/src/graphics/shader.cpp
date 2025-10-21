#include "../../include/graphics/shader.hpp"

using namespace ducky;
using namespace ducky::graphics;

Shader::Shader() {
  std::string vert_str = File::read("assets/shaders/vertex.glsl");
  std::string frag_str = File::read("assets/shaders/fragment.glsl");

  size_t point_define_pos = frag_str.find("#define MAX_POINT_LIGHTS");
  if (point_define_pos != std::string::npos) {
    size_t end_line = frag_str.find("\n", point_define_pos);
    frag_str.replace(point_define_pos, end_line - point_define_pos,
                     "#define MAX_POINT_LIGHTS " +
                         std::to_string(Renderer::get_max_point_lights()));
  }

  size_t spot_define_pos = frag_str.find("#define MAX_SPOT_LIGHTS");
  if (spot_define_pos != std::string::npos) {
    size_t end_line = frag_str.find("\n", spot_define_pos);
    frag_str.replace(spot_define_pos, end_line - spot_define_pos,
                     "#define MAX_SPOT_LIGHTS " +
                         std::to_string(Renderer::get_max_spot_lights()));
  }

  size_t directional_define_pos =
      frag_str.find("#define MAX_DIRECTIONAL_LIGHTS");
  if (directional_define_pos != std::string::npos) {
    size_t end_line = frag_str.find("\n", directional_define_pos);
    frag_str.replace(
        directional_define_pos, end_line - directional_define_pos,
        "#define MAX_DIRECTIONAL_LIGHTS " +
            std::to_string(Renderer::get_max_directional_lights()));
  }

  const char* vert = vert_str.c_str();
  const char* frag = frag_str.c_str();

  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &vert, NULL);
  glCompileShader(vert_shader);
  check_compile(vert_shader, "VERTEX");

  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &frag, NULL);
  glCompileShader(frag_shader);
  check_compile(frag_shader, "FRAGMENT");

  this->id = glCreateProgram();

  glAttachShader(this->id, vert_shader);
  glAttachShader(this->id, frag_shader);
  glLinkProgram(this->id);
  check_link();

  GLint is_program = glIsProgram(this->id);
  std::cout << "Is valid program: " << is_program << std::endl;

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
  check_compile(vert_shader, "VERTEX");

  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &frag, NULL);
  glCompileShader(frag_shader);
  check_compile(frag_shader, "FRAGMENT");

  this->id = glCreateProgram();

  glAttachShader(this->id, vert_shader);
  glAttachShader(this->id, frag_shader);
  glLinkProgram(this->id);
  check_link();

  GLint is_program = glIsProgram(this->id);
  std::cout << "Is valid program: " << is_program << std::endl;

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);
}

Shader::~Shader() { this->destroy(); }

void Shader::activate() {
  glUseProgram(this->id);
  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    std::cerr << "glUseProgram error: " << err << std::endl;
  }
}

void Shader::destroy() { glDeleteProgram(this->id); }

void Shader::check_compile(GLuint shader, std::string type) {
  GLint success;
  GLchar info_log[1024];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 1024, NULL, info_log);
    std::cout << "Shader compilation failed (" << type << "):\n"
              << info_log << std::endl;
  }
}

void Shader::check_link() {
  GLint success;
  GLchar info_log[1024];
  glGetProgramiv(id, GL_LINK_STATUS, &success);

  GLint log_length;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);
  std::cout << "Program link log length: " << log_length << std::endl;

  if (!success) {
    glGetProgramInfoLog(id, 1024, NULL, info_log);
    std::cerr << "Program linking failed:\n" << info_log << std::endl;
  }
}