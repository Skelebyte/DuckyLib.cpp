#include "../../include/ecs/entity_registry.hpp"

using namespace ducky::ecs;

std::vector<Entity*> EntityRegistry::entities_;

void EntityRegistry::register_entity(Entity* entity) {
  entities_.push_back(entity);
}

std::vector<Entity*>& EntityRegistry::get_entities() { return entities_; }

void EntityRegistry::update() {
  for (Entity* entity : entities_) {
    entity->update();
  }
}

Entity* EntityRegistry::get_entity_by_id(unsigned int id) {
  for (Entity* entity : entities_) {
    if (entity->get_id() == id) {
      return entity;
    }
  }
  return nullptr;
}