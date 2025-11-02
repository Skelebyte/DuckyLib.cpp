#pragma once

#include "entity.hpp"

namespace ducky::ecs {

class EntityRegistry {
 public:
  static void register_entity(Entity* entity);
  static std::vector<Entity*>& get_entities();
  static void update();

 private:
  static std::vector<Entity*> entities_;
};

}  // namespace ducky::ecs