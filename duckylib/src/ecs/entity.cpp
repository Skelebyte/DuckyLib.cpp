#include "../../include/ecs/entity.hpp"
#include "../../include/ecs/entity_registry.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::tools;
using namespace ducky::math;

Entity::Entity(std::string name, std::string tag) : Object(), transform() {
  this->name = name;
  this->tag = tag;
  enabled = true;
  EntityRegistry::register_entity(this);
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

void Entity::save(std::string path) {}

void Entity::load(std::string path) {}

EntityType Entity::get_type() const { return type_; }

void Entity::add_entity_data() {
  add("name", name, "entity");
  add("tag", tag, "entity");
  add("enabled", std::to_string(enabled), "entity");
  add("type_", std::to_string(static_cast<int>(type_)), "entity");

  add("position", transform.position.to_string(), "transform");
  add("rotation", transform.rotation.to_string(), "transform");
  add("scale", transform.scale.to_string(), "transform");
}

void Entity::load_entity_data(std::string path) {
  name = get(path, "name", "entity");
  tag = get(path, "tag", "entity");
  enabled = std::stoi(get(path, "enabled", "entity"));
  type_ = (EntityType)std::stoi(get(path, "type_", "entity"));

  transform.position = Vec3::from_string(get(path, "position", "transform"));
  transform.rotation = Vec3::from_string(get(path, "rotation", "transform"));
  transform.scale = Vec3::from_string(get(path, "scale", "transform"));
}