#include "../../include/ecs/ecs.hpp"

using namespace ducky;
using namespace ducky::ecs;

ECS::ECS() {
  this->next_id_ = 0;
  entities = std::vector<Entity*>();
}

ECS::~ECS() {
  for (Entity* entity : this->entities) {
    delete entity;
  }
  this->entities.clear();
  for (Component* component : this->components) {
    delete component;
  }
  this->components.clear();
  next_id_ = 0;
}

unsigned int ECS::get_next_id() { return next_id_; }

unsigned int ECS::new_entity() {
  this->entities.push_back(new Entity(next_id_));
  next_id_++;
  return next_id_ - 1;
}

Entity* ECS::get_entity(unsigned int id) {
  for (Entity* entity : this->entities) {
    if (entity->get_id() == id) {
      return entity;
    }
  }
  return nullptr;
}