#pragma once

#include <vector>
#include "object.hpp"

namespace ducky {
class ObjectRegistry {
 public:
  static unsigned int register_object(Object* object);
  static std::vector<Object*>& get_objects();

 private:
  static std::vector<Object*> objects_;
  static unsigned int next_id_;
};
}  // namespace ducky