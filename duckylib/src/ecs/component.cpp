#include "../../include/ecs/component.hpp"

using namespace ducky;
using namespace ducky::ecs;

Component::Component(std::string name) { this->name_ = name; }

void Component::destroy() {
  std::cout << "Destroying " << this->get_id() << ", " << this->name_
            << std::endl;
  this->owner_ = nullptr;
  destroy();
}