#pragma once

#include <iostream>
#include <vector>
#include "component.hpp"
#include "components/transform.hpp"
#include "object.hpp"

namespace ducky {

namespace ecs {

class Entity : public Object {
 public:
  Entity();
  Entity(std::string name);
  ~Entity();
  void destroy();

  void update();

  template <typename T>
  T* add_component(T* component) {
    component->owner = this;
    this->components_.push_back(component);
    return component;
  }

  template <typename T>
  T* get_component() {
    for (int i = 0; i < components_.size(); i++) {
      if (typeid(components_[i]) == typeid(T)) {
        return (T*)components_[i];
      }
    }
    std::cout << "not found!\n";
    return nullptr;
  }

  void remove_component(Component* component);

  bool has_component(Component* component);

  template <typename T>
  bool has_component_of_type() {
    for (int i = 0; i < this->components_.size(); i++) {
      if (typeid(this->components_[i]) == typeid(T)) {
        return true;
      }
    }
    return false;
  }

  Entity* get_parent();

  void add_child(Entity* child);

  Entity* get_child(std::string name);
  Entity* get_child(int id);

  bool has_child(std::string name);
  bool has_child(int id);

  std::string name;

  components::Transform transform;

 private:
  std::vector<Component*> components_;
  std::vector<Entity*> children_;
  Entity* parent_;
};

}  // namespace ecs

}  // namespace ducky
