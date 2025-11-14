#pragma once

#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../third_party/imgui/imgui.h"
#include "../third_party/imgui/imgui_impl_opengl3.h"
#include "../third_party/imgui/imgui_impl_sdl3.h"
#include "tools/asset_manager.hpp"
#include "utils/file.hpp"

namespace ducky {
class Object {
 public:
  Object();
  virtual void destroy();
  virtual void imgui_widget() = 0;
  int get_id();
  void register_object();
  bool auto_register = false;

 protected:
  bool destroyed;

 private:
  int id_;
};

}  // namespace ducky
