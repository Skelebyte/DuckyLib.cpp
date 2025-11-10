#pragma once

#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include "../third_party/imgui/imgui.h"
#include "../third_party/imgui/imgui_impl_opengl3.h"
#include "../third_party/imgui/imgui_impl_sdl3.h"

namespace ducky {
class Object {
 public:
  Object();
  virtual void destroy();
  virtual void imgui_widget() = 0;
  int get_id();

 protected:
  bool destroyed;

 private:
  int id_;
};

}  // namespace ducky
