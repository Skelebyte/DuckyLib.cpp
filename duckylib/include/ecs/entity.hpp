#pragma once

#include <iostream>
#include <vector>
#include "../math/vec3.hpp"
#include "../object.hpp"
#include "../utils/serializable.hpp"
#include "transform.hpp"

namespace ducky {

namespace ecs {

enum EntityType {
  GENERIC = 0,
  MESH_RENDERER = 1,
  CAMERA = 2,
  EDITOR_CAMERA = 3,
  POINT_LIGHT = 4,
  SPOT_LIGHT = 5,
  DIRECTIONAL_LIGHT = 6
};

class Entity : public Object, public utils::Serializable {
 public:
  Entity(std::string name, std::string tag = "entity");
  virtual ~Entity() = 0;
  void destroy();

  virtual void update() = 0;
  virtual void imgui_widget() = 0;

  Entity* get_parent();

  void add_child(Entity* child);

  Entity* get_child(std::string name);
  Entity* get_child(int id);

  bool has_child(std::string name);
  bool has_child(int id);

  void save(std::string path) override;
  void load(std::string path) override;
  EntityType get_type() const;

  std::string name;
  std::string tag;

  Transform transform;

  bool enabled;

 protected:
  EntityType type_;
  void add_entity_data();
  void load_entity_data(std::string path);

 private:
  std::vector<Entity*> children_;
  Entity* parent_;
};

}  // namespace ecs

}  // namespace ducky
