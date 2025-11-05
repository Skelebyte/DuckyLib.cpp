#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <iostream>
#include <memory>
#include "runtime_err.hpp"
#include "time.hpp"

namespace ducky {
class App {
 public:
  App(const char* arg);
  ~App();
  static std::string set_project_name();
  static std::string get_project_name();

 private:
  bool dev_mode_ = false;
  std::string project_name_;
};
}  // namespace ducky