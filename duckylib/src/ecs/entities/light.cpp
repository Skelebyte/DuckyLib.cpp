#include "../../../include/ecs/entities/light.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::ecs::components;
using namespace ducky::graphics;
using namespace ducky::math;

Light::Light() : Entity("light") {}

Light::Light(Shader* shader) : Entity("light") { shader_ = shader; }

Light::~Light() {}

void Light::update() {}