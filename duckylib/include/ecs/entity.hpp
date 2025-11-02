#pragma once

#include <iostream>
#include <vector>
#include "../object.hpp"
#include "transform.hpp"

namespace ducky {

namespace ecs {

class Entity : public Object {
 public:
  Entity(std::string name);
  ~Entity();
  void destroy();

  virtual void update() = 0;

  Entity* get_parent();

  void add_child(Entity* child);

  Entity* get_child(std::string name);
  Entity* get_child(int id);

  bool has_child(std::string name);
  bool has_child(int id);

  std::string name;

  Transform transform;

  bool enabled;

 private:
  std::vector<Entity*> children_;
  Entity* parent_;
};

}  // namespace ecs

}  // namespace ducky
