#include "../../../include/ecs/entities/light.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::graphics;
using namespace ducky::math;

Light::Light(LightType type) : Entity("light", "light") {
  light_type_ = type;
  intensity = 1.0f;
  // shadow_map_shader_ = Shader("assets/shaders/shadow_map_vertex.glsl",
  //                             "assets/shaders/shadow_map_fragment.glsl");
  Renderer::add_light(this);
}

Light::~Light() {}

void Light::update() {
  ortho_projection_.orthogonal(-35.0f, 35.0f, 35.0f, -35.0f, 0.1f, 75.0f);
  light_view_.look_at(transform.position * 20.0f, Vec3(0, 0, 0), Vec3(0, 1, 0));
  light_projection_ = ortho_projection_ * light_view_;

  // shadow_map_shader_.activate();
  // glUniformMatrix4fv(
  //     glGetUniformLocation(shadow_map_shader_.id, "light_projection"), 1,
  //     GL_FALSE, light_projection_.data);
}

void Light::imgui_widget() {
  transform.imgui_widget();
  ImGui::ColorEdit3("Color", color.data);
  ImGui::DragFloat("Intensity", &intensity, 0.1f, 0.0f, 100.0f);
}

LightType Light::get_type() const { return light_type_; }

PointLight::PointLight(float _a, float _b, float inten)
    : Light(LightType::POINT) {
  name = "point_light";
  tag = "point_light";
  a = _a;
  b = _b;
  intensity = inten;
}

void PointLight::imgui_widget() {
  Light::imgui_widget();
  ImGui::DragFloat("Constant (a)", &a, 0.01f, 0.0f, 10.0f);
  ImGui::DragFloat("Linear (b)", &b, 0.001f, 0.0f, 1.0f);
}

void Light::save(std::string path) {}
void Light::load(std::string path) {}

SpotLight::SpotLight(float inner, float outer, float inten)
    : Light(LightType::SPOT) {
  name = "spot_light";
  tag = "spot_light";
  inner_cone = inner;
  outer_cone = outer;
  intensity = inten;
}

void SpotLight::imgui_widget() {
  Light::imgui_widget();
  ImGui::DragFloat("Inner Cone Angle", &inner_cone, 0.1f, 0.0f, 90.0f);
  ImGui::DragFloat("Outer Cone Angle", &outer_cone, 0.1f, 0.0f, 90.0f);
}

DirectionalLight::DirectionalLight(float inten)
    : Light(LightType::DIRECTIONAL) {
  name = "directional_light";
  tag = "directional_light";
  intensity = inten;
}

void DirectionalLight::imgui_widget() { Light::imgui_widget(); }