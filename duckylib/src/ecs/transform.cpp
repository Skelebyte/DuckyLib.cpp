#include "../../include/ecs/transform.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::math;
using namespace ducky::tools;
using namespace ducky::utils;

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
  // this->rotation.x = Mathf::degrees(this->rotation.x);
  // this->rotation.y = Mathf::degrees(this->rotation.y);
  // this->rotation.z = Mathf::degrees(this->rotation.z);

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

void Transform::imgui_widget() {
  ImGui::DragFloat3("Position", this->position.data, 0.1f);
  ImGui::DragFloat3("Rotation", this->rotation.data, 0.1f);
  ImGui::DragFloat3("Scale", this->scale.data, 0.1f, -100.0f, 100.0f);
}

void Transform::save(std::string path) {
  std::string pos_data = position.to_string();
  std::string rot_data = rotation.to_string();
  std::string scale_data = scale.to_string();

  nlohmann::json json;
  json["position"] = pos_data;
  json["rotation"] = rot_data;
  json["scale"] = scale_data;

  File::write(json.dump(), path + "_tfm", true);
}

void Transform::load(std::string path) {
  if (AssetManager::is_path_valid(path + "_tfm") == false) {
    return;
  }

  std::ifstream f = std::ifstream(path + "_tfm");
  nlohmann::json json = nlohmann::json::parse(f);
  f.close();

  position = Vec3::from_string(json["position"]);
  rotation = Vec3::from_string(json["rotation"]);
  scale = Vec3::from_string(json["scale"]);
}