#include "../../include/utils/serializable.hpp"

using namespace ducky;
using namespace ducky::utils;

void Serializable::add(std::string name, std::string value,
                       std::string parent) {
  if (parent != "") {
    json_[parent][name] = value;
    return;
  }

  json_[name] = value;
}

std::string Serializable::get(std::string path, std::string name,
                              std::string parent) {
  std::ifstream f = std::ifstream(path);
  nlohmann::json temp = nlohmann::json::parse(f);
  f.close();

  if (parent != "") {
    return temp[parent][name];
  } else {
    return temp[name];
  }
}

std::string Serializable::get(std::string path, std::string name,
                              std::string parent) {
  std::ifstream f = std::ifstream(path);
  nlohmann::json temp = nlohmann::json::parse(f);
  f.close();

  if (parent != "") {
    return temp[parent][name];
  } else {
    return temp[name];
  }
}

void Serializable::write(std::string path) {
  if (!allow_saving)
    return;
  File::write(json_.dump(2), path, true);
}