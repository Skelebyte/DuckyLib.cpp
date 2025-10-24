#include "../../include/ecs/component.hpp"

using namespace ducky;
using namespace ducky::ecs;

Component::Component(std::string name) { this->name = name; }

void Component::destroy() {
  std::cout << "Destroying " << this->get_id() << ", " << this->name
            << std::endl;
  this->owner = nullptr;
  destroy();
}