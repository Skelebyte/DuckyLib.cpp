#pragma once

#include <iostream>
#include "../../graphics/color.hpp"
#include "../../graphics/shader.hpp"
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
  LightType get_type() const;
  graphics::Color color = graphics::Color::white();
  float intensity;

 private:
  LightType light_type_;
};

class PointLight : public Light {
 public:
  PointLight(float _a = 0.56f, float _b = 0.08f, float inten = 1.0f);
  float a;
  float b;
};

class SpotLight : public Light {
 public:
  SpotLight(float inner = 18.2f, float outer = 25.8f, float inten = 1.0f);
  float inner_cone;
  float outer_cone;
};

class DirectionalLight : public Light {
 public:
  DirectionalLight(float inten = 1.0f);
};

}  // namespace entities

}  // namespace ecs

}  // namespace ducky
