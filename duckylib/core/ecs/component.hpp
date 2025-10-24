#pragma once

#include <iostream>
#include "../object.hpp"

namespace ducky {

namespace ecs {

class Component : public Object {
 public:
  Component(std::string name);
  void destroy() override;
  virtual void process() = 0;

 public:
  std::string name;
  Object* owner;
};

}  // namespace ecs

}  // namespace ducky
