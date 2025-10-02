#include "../../include/math/vec3.hpp"

using namespace ducky;
using namespace ducky::math;

void Vec3::zero() {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
}

Vec3::Vec3() {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
}

Vec3::Vec3(float x_, float y_, float z_) {
  x = x_;
  y = y_;
  z = z_;
}

float Vec3::length() const { return sqrt(x * x + y * y); }

Vec3 Vec3::normalized() {
  if (length() == 0.0f) {
    return Vec3(0.0f, 0.0f, 0.0f);
  }
  Vec3 result = Vec3(x / length(), y / length(), z / length());
  return result;
}

float Vec3::dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

Vec3 Vec3::cross(Vec3 a, Vec3 b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

void Vec3::operator+=(const Vec3& other) {
  x += other.x;
  y += other.y;
  z += other.z;
}

void Vec3::operator-=(const Vec3& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
}

bool Vec3::operator==(const Vec3& other) const {
  return (x == other.x && y == other.y && z == other.z);
}