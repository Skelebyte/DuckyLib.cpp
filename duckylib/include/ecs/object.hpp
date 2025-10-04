#pragma once

#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace ducky {

namespace ecs {

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

}  // namespace ecs

}  // namespace ducky