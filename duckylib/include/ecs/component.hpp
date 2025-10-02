#pragma once

namespace ducky {

namespace ecs {
class Component {
 public:
  Component(unsigned int& entity_id);
  ~Component();

 private:
  unsigned int& entity_id_;
};
}  // namespace ecs

}  // namespace ducky