#include "../../include/graphics/material.hpp"

using namespace ducky::graphics;
using namespace ducky::utils;
using namespace ducky::tools;

Material::Material(Texture* diff, Texture* spec, Color col) : Object() {
  diffuse = diff;
  specular = spec;
  color = col;
  specular_strength = 0.5f;
  unlit = false;
}

Material::~Material() {
  // std::cout << "material destructor\n";
  delete diffuse;
  delete specular;
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

  unlit_uniform = glGetUniformLocation(shader->id, "unlit");
  Renderer::get_gl_error("Material::get_uniforms - unlit uniform");
}

void Material::bind() {
  glActiveTexture(GL_TEXTURE0);
  diffuse->bind();
  Renderer::get_gl_error("Material::bind - diffuse.bind");
  glActiveTexture(GL_TEXTURE1);
  specular->bind();
  Renderer::get_gl_error("Material::bind - specular.bind");
}

void Material::unbind() {
  diffuse->unbind();
  Renderer::get_gl_error("Material::unbind - diffuse.unbind");
  specular->unbind();
  Renderer::get_gl_error("Material::unbind - specular.unbind");
}

void Material::imgui_widget() {
  ImGui::Text("Material");
  ImGui::Checkbox("Unlit", &unlit);
  if (ImGui::InputText("Diffuse Path", (char*)diffuse->path.c_str(), 256)) {
    delete diffuse;
    diffuse = new Texture(std::string(diffuse->path));
  }
  if (diffuse->path != "" || diffuse->is_valid() == false) {
    ImGui::Image(ImTextureRef(diffuse->id), ImVec2(64, 64));
  }
  if (ImGui::InputText("Specular Path", (char*)specular->path.c_str(), 256)) {
    delete specular;
    specular = new Texture(std::string(specular->path));
  }
  if (specular->path != "" || specular->is_valid() == false) {
    ImGui::Image(ImTextureRef(specular->id), ImVec2(64, 64));
  }

  ImGui::DragFloat("Specular Strength", &specular_strength, 0.01f, 0.0f, 10.0f);
  ImGui::ColorEdit4("Color", color.data);
}
