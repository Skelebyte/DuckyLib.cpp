#pragma once

#include <iostream>
#include "../../graphics/color.hpp"
#include "../../graphics/shader.hpp"
#include "../../math/mat4.hpp"
#include "../entity.hpp"

namespace ducky {

namespace ecs {

namespace entities {

typedef enum { POINT, SPOT, DIRECTIONAL } LightType;

class Light : public Entity {
 public:
  Light(LightType type = LightType::POINT);
  ~Light();
  void update() override;
  void imgui_widget() override;
  LightType get_type() const;
  graphics::Color color = graphics::Color::white();
  float intensity;
  void save(std::string path) override;
  void load(std::string path) override;

 protected:
  math::Mat4 ortho_projection_;
  math::Mat4 light_view_;
  math::Mat4 light_projection_;
  graphics::Shader shadow_map_shader_;

 private:
  LightType light_type_;
};

class PointLight : public Light {
 public:
  PointLight(float _a = 0.56f, float _b = 0.08f, float inten = 1.0f);
  void imgui_widget() override;
  float a;
  float b;
};

class SpotLight : public Light {
 public:
  SpotLight(float inner = 18.2f, float outer = 25.8f, float inten = 1.0f);
  void imgui_widget() override;
  float inner_cone;
  float outer_cone;
};

class DirectionalLight : public Light {
 public:
  DirectionalLight(float inten = 1.0f);
  void imgui_widget() override;
};

}  // namespace entities

}  // namespace ecs

}  // namespace ducky
