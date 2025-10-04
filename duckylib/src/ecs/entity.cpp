#include "../../include/ecs/entity.hpp"

using namespace ducky;
using namespace ducky::ecs;

Entity::Entity() { this->name = "game_object"; }

Entity::Entity(std::string name) { this->name = name; }

Entity::~Entity() { destroy(); }

void Entity::destroy() {
  for (int i = 0; i < this->components_.size(); i++) {
    std::cout << "hi mum!\n";
    this->components_[i]->destroy();
  }
  this->components_.clear();

  for (int i = 0; i < this->children_.size(); i++) {
    this->children_[i]->destroy();
  }
  this->children_.clear();
}

void Entity::add_component(Component* component) {
  component->owner_ = this;
  this->components_.push_back(component);
}

void Entity::remove_component(Component* component) {
  bool found_comp = false;
  int comp_index = 0;
  for (int i = 0; i < this->components_.size(); i++) {
    if (this->components_[i]->get_id() == component->get_id()) {
      found_comp = true;
      comp_index = i;
      break;
    }
  }

  if (found_comp == false)
    return;  // throw warning, cant find target component

  component->owner_ = nullptr;
  // maybe dont destroy component? what if we want to place that component on
  // another Entity?
  this->components_[comp_index]->destroy();
  this->components_.erase(components_.begin() + comp_index);
}

bool Entity::has_component(Component* component) {
  int comp_index = 0;
  for (int i = 0; i < this->components_.size(); i++) {
    if (this->components_[i]->get_id() == component->get_id()) {
      return true;
    }
  }

  return false;  // throw warning, cant find target component
}

template <typename T>
bool Entity::has_component_of_type() {
  for (int i = 0; i < this->components_.size(); i++) {
    if (typeid(this->components_[i]) == typeid(T)) {
      return true;
    }
  }
  return false;
}

Entity* Entity::get_parent() { return parent_; }

void Entity::add_child(Entity* child) {
  if (child->get_parent() != nullptr) {
    std::cout << "Entity " << child->get_parent()->name << " ("
              << child->get_parent()->get_id() << ") is the parent of "
              << child->name << " (" << child->get_id()
              << "). Can't change ownership of child to " << name << " ("
              << get_id() << ")\n";
    return;
  }
  this->children_.push_back(child);
  child->parent_ = this;
}

Entity* Entity::get_child(std::string name) {
  for (int i = 0; i < this->children_.size(); i++) {
    if (this->children_[i]->name == name) {
      return this->children_[i];
    }
  }
  return nullptr;
}

Entity* Entity::get_child(int id) {
  for (int i = 0; i < this->children_.size(); i++) {
    if (this->children_[i]->get_id() == id) {
      return this->children_[i];
    }
  }
  return nullptr;
}

bool Entity::has_child(std::string name) {
  for (int i = 0; i < this->children_.size(); i++) {
    if (this->children_[i]->name == name) {
      return true;
    }
  }
  return false;
}

bool Entity::has_child(int id) {
  for (int i = 0; i < this->children_.size(); i++) {
    if (this->children_[i]->get_id() == id) {
      return true;
    }
  }
  return false;
}

template <typename T>
T Entity::get_component() {
  for (int i = 0; i < components_.size(); i++) {
    if (typeid(components_[i]) == typeid(T)) {
      return (T)components_[i];
    }
  }
  return nullptr;
}