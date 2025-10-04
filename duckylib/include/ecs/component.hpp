#pragma once

#include <iostream>
#include "object.hpp"

namespace ducky {

namespace ecs {

class Component : public Object {
 public:
  Component(std::string name);
  void destroy() override;

 public:
  std::string name_;
  Object* owner_;
};

}  // namespace ecs

}  // namespace ducky
