#pragma once

#include <iostream>
#include <vector>
#include "component.hpp"
#include "object.hpp"

namespace ducky {

namespace ecs {

class Entity : public Object {
 public:
  Entity();
  Entity(std::string name);
  ~Entity();

  void destroy();

  void add_component(Component* component);

  void remove_component(Component* component);

  bool has_component(Component* component);

  template <typename T>
  bool has_component_of_type();

  Entity* get_parent();

  void add_child(Entity* child);

  Entity* get_child(std::string name);
  Entity* get_child(int id);

  bool has_child(std::string name);
  bool has_child(int id);

  template <typename T>
  T get_component();

 public:
  std::string name;

 private:
  std::vector<Component*> components_;
  std::vector<Entity*> children_;
  Entity* parent_;
};

}  // namespace ecs

}  // namespace ducky
