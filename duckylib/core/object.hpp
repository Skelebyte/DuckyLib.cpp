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
  unsigned int get_id();

 protected:
  bool destroyed_;

 private:
  unsigned int id_;
};

}  // namespace ducky