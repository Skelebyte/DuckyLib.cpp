#include "../../include/ecs/entity.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::components;

Entity::Entity() : transform() {
  this->name = "entity";
  enabled = true;
}

Entity::Entity(std::string name) : transform() {
  this->name = name;
  enabled = true;
}

Entity::~Entity() { /*destroy();*/ }

void Entity::destroy() {
  for (int i = 0; i < this->children_.size(); i++) {
    this->children_[i]->destroy();
  }
  this->children_.clear();
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
