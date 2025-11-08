#pragma once

#include "entity.hpp"

namespace ducky::ecs {

class EntityRegistry {
 public:
  static void register_entity(Entity* entity);
  static std::vector<Entity*>& get_entities();
  static void update();
  static Entity* get_entity_by_id(unsigned int id);

 private:
  static std::vector<Entity*> entities_;
};

}  // namespace ducky::ecs