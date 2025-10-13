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
  Vec3 result = Vec3();

  // result.x = cos(Mathf::to_degrees(this->rotation.x)) *
  //            sin(Mathf::to_degrees(this->rotation.y));
  // result.y = -sin(Mathf::to_degrees(this->rotation.x));
  // result.z = cos(Mathf::to_degrees(this->rotation.x)) *
  //            cos(Mathf::to_degrees(this->rotation.y));

  result = Vec3(0, 0, -1);

  return result.normalized();
}

Vec3 Transform::right() const {
  Vec3 result = Vec3();

  // result.x = cos(Mathf::to_degrees(this->rotation.y));
  // result.y = 0;
  // result.z = sin(Mathf::to_degrees(this->rotation.y));

  result = Vec3(1, 0, 0);

  return result.normalized();
}

Vec3 Transform::up() const {
  Vec3 result = Vec3(0, 1, 0);

  return result.normalized();
}

void Transform::process() {
  // this->rotation.x = Mathf::to_degrees(this->rotation.x);
  // this->rotation.y = Mathf::to_degrees(this->rotation.y);
  // this->rotation.z = Mathf::to_degrees(this->rotation.z);

  // if (this->rotation.x > 360.0f)
  //   this->rotation.x -= 360.0f;
  // if (this->rotation.x < 0.0f)
  //   this->rotation.x += 360.0f;

  // if (this->rotation.y > 360.0f)
  //   this->rotation.y -= 360.0f;
  // if (this->rotation.y < 0.0f)
  //   this->rotation.y += 360.0f;

  // if (this->rotation.z > 360.0f)
  //   this->rotation.z -= 360.0f;
  // if (this->rotation.z < 0.0f)
  //   this->rotation.z += 360.0f;

  // this->rotation.x = Mathf::to_radians(this->rotation.x);
  // this->rotation.y = Mathf::to_radians(this->rotation.y);
  // this->rotation.z = Mathf::to_radians(this->rotation.z);
}