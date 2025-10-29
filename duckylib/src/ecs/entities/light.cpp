#include "../../../include/ecs/entities/light.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::graphics;
using namespace ducky::math;

Light::Light(LightType type) : Entity("light") {
  light_type_ = type;
  intensity = 1.0f;
}

Light::~Light() {}

void Light::update() {}

LightType Light::get_type() const { return light_type_; }

PointLight::PointLight(float _a, float _b, float inten)
    : Light(LightType::POINT) {
  a = _a;
  b = _b;
  intensity = inten;
}

SpotLight::SpotLight(float inner, float outer, float inten)
    : Light(LightType::SPOT) {
  inner_cone = inner;
  outer_cone = outer;
  intensity = inten;
}

DirectionalLight::DirectionalLight(float inten)
    : Light(LightType::DIRECTIONAL) {
  intensity = inten;
}