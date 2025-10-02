#pragma once

#include <iostream>
#include <vector>
#include "component.hpp"
#include "entity.hpp"

namespace ducky {

namespace ecs {

#define ENTITY unsigned int

class ECS {
 public:
  ECS();
  ~ECS();
  unsigned int get_next_id();
  unsigned int new_entity();
  Entity* get_entity(unsigned int id);
  std::vector<Entity*> entities;
  std::vector<Component*> components;

 private:
  unsigned int next_id_;
};
}  // namespace ecs

}  // namespace ducky