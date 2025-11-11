#include "../../include/ecs/entity_registry.hpp"

using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::utils;

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

void EntityRegistry::create_entity_from_file(std::string path) {
  std::ifstream f = std::ifstream(path);
  nlohmann::json temp = nlohmann::json::parse(f);
  f.close();

  int type = std::stoi(Serializable::get(path, "type_", "entity_data"));

  switch (type) {
    case EntityType::MESH_RENDERER:
      auto* mesh_renderer = new MeshRenderer();
      break;

    default:
      break;
  }
}