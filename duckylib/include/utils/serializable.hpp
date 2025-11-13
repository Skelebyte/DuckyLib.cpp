#pragma once

#include <iostream>
#include "../../third_party/json.hpp/json.hpp"
#include "file.hpp"

namespace ducky::utils {
class Serializable {
 public:
  void add(std::string name, std::string value, std::string parent = "");
  void write(std::string path);
  std::string get(std::string path, std::string name, std::string parent = "");
  static std::string static_get(std::string path, std::string name,
                                std::string parent = "");
  virtual void save(std::string path) = 0;
  virtual void load(std::string path) = 0;
  bool allow_saving = true;

 private:
  nlohmann::json json_;
};

}  // namespace ducky::utils