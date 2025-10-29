#pragma once

#include <iostream>
#include "../../third_party/glad/glad.h"
#include "../object.hpp"
#include "color.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace ducky::graphics {
class Material : public Object {
 public:
  Material(Texture diff = Texture(),
           Texture spec = Texture(DEFAULT_TEXTURE_SPEC),
           Color col = Color::white());
  void get_uniforms(Shader* shader);
  void bind();
  void unbind();

  Texture diffuse;
  Texture specular;
  Color color;
  float specular_strength;

  GLuint diffuse_uniform;
  GLuint specular_uniform;
  GLuint specular_strength_uniform;
  GLuint color_uniform;
};
}  // namespace ducky::graphics