#pragma once

#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace ducky {
class Object {
 public:
  Object();

  virtual void destroy();
  int get_id();

 protected:
  bool destroyed;

 private:
  int id_;
};

}  // namespace ducky
