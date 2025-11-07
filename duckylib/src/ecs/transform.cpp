#include "../../include/ecs/transform.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::math;

Transform::Transform() : Object() {
  this->position = Vec3(0.0f, 0.0f, 0.0f);
  this->rotation = Vec3(0.0f, 0.0f, 0.0f);
  this->scale = Vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(Vec3 pos, Vec3 rot, Vec3 sca) : Object() {
  this->position = pos;
  this->rotation = rot;
  this->scale = sca;
}

Vec3 Transform::forward() const {
  Vec3 forward = Vec3(0, 0, -1);
  forward.rotate(rotation.x, Vec3(1, 0, 0));
  forward.rotate(rotation.y, Vec3(0, 1, 0));
  forward.rotate(rotation.z, Vec3(0, 0, -1));

  return forward;
}

Vec3 Transform::right() const {
  Vec3 result = Vec3();

  // result.x = cos(Mathf::degrees(this->rotation.y));
  // result.y = 0;
  // result.z = sin(Mathf::degrees(this->rotation.y));

  result = Vec3(1, 0, 0);

  return result.normalized();
}

Vec3 Transform::up() const {
  Vec3 result = Vec3(0, 1, 0);

  return result.normalized();
}

void Transform::process() {
  this->rotation.x = Mathf::degrees(this->rotation.x);
  this->rotation.y = Mathf::degrees(this->rotation.y);
  this->rotation.z = Mathf::degrees(this->rotation.z);

  if (this->rotation.x > 360.0f)
    this->rotation.x -= 360.0f;
  if (this->rotation.x < 0.0f)
    this->rotation.x += 360.0f;

  if (this->rotation.y > 360.0f)
    this->rotation.y -= 360.0f;
  if (this->rotation.y < 0.0f)
    this->rotation.y += 360.0f;

  if (this->rotation.z > 360.0f)
    this->rotation.z -= 360.0f;
  if (this->rotation.z < 0.0f)
    this->rotation.z += 360.0f;

  // this->rotation.x = Mathf::radians(this->rotation.x);
  // this->rotation.y = Mathf::radians(this->rotation.y);
  // this->rotation.z = Mathf::radians(this->rotation.z);
}