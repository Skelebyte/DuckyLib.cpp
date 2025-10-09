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

Vec3 Transform::forward() const {
  float yaw = Mathf::to_radians(this->rotation.y);
  float pitch = Mathf::to_radians(this->rotation.x);

  return Vec3(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
}

Vec3 Transform::right() const {
  float yaw = Mathf::to_radians(this->rotation.y);
  float pitch = Mathf::to_radians(this->rotation.x);

  Vec3 result = Vec3(sin(yaw - Mathf::to_radians(90.0f)), 0,
                     cos(yaw - Mathf::to_radians(90.0f)))
                    .normalized();
  return result;
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