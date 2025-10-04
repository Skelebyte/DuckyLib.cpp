#include "../../../include/ecs/components/transform.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::components;
using namespace ducky::math;

Transform::Transform() : Component("Transform") {
  this->position = Vec3(0.0f, 0.0f, 0.0f);
  this->rotation = Vec3(0.0f, 0.0f, 0.0f);
  this->scale = Vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(Vec3 pos, Vec3 rot, Vec3 sca) : Component("Transform") {
  this->position = pos;
  this->rotation = rot;
  this->scale = sca;
}

void Transform::process() {
  if (this->rotation.x > 360.0f)
    this->rotation.x -= 360.0f;
  if (this->rotation.x < 360.0f)
    this->rotation.x += 360.0f;

  if (this->rotation.y > 360.0f)
    this->rotation.y -= 360.0f;
  if (this->rotation.y < 360.0f)
    this->rotation.y += 360.0f;

  if (this->rotation.z > 360.0f)
    this->rotation.z -= 360.0f;
  if (this->rotation.z < 360.0f)
    this->rotation.z += 360.0f;
}