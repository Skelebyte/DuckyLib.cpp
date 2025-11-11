#pragma once

#include <iostream>
#include "../../third_party/json.hpp/json.hpp"
#include "../utils/serializable.hpp"
#include "entities/camera.hpp"
#include "entities/editor_camera.hpp"
#include "entities/light.hpp"
#include "entities/mesh_renderer.hpp"
#include "entity.hpp"

namespace ducky::ecs {

class EntityRegistry {
 public:
  static void register_entity(Entity* entity);
  static std::vector<Entity*>& get_entities();
  static void update();
  static Entity* get_entity_by_id(unsigned int id);
  static void create_entity_from_file(std::string path);

 private:
  static std::vector<Entity*> entities_;
};

}  // namespace ducky::ecs