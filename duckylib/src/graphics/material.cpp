#include "../../include/graphics/material.hpp"

using namespace ducky::graphics;

Material::Material(Texture diff, Texture spec, Color col) {
  diffuse = diff;
  specular = spec;
  color = col;
  specular_strength = 0.5f;
}

void Material::get_uniforms(Shader* shader) {
  diffuse_uniform = glGetUniformLocation(shader->id, "diffuse_texture");
  Renderer::get_gl_error("Material::get_uniforms - diffuse uniform");
  specular_uniform = glGetUniformLocation(shader->id, "specular_texture");
  Renderer::get_gl_error("Material::get_uniforms - specular uniform");
  color_uniform = glGetUniformLocation(shader->id, "color");
  Renderer::get_gl_error("Material::get_uniforms - color uniform");
  specular_strength_uniform =
      glGetUniformLocation(shader->id, "specular_strength");
  Renderer::get_gl_error("Material::get_uniforms - specular strength uniform");
}

void Material::bind() {
  glActiveTexture(GL_TEXTURE0);
  diffuse.bind();
  Renderer::get_gl_error("Material::bind - diffuse.bind");
  glActiveTexture(GL_TEXTURE1);
  specular.bind();
  Renderer::get_gl_error("Material::bind - specular.bind");
}

void Material::unbind() {
  diffuse.unbind();
  Renderer::get_gl_error("Material::unbind - diffuse.unbind");
  specular.unbind();
  Renderer::get_gl_error("Material::unbind - specular.unbind");
}