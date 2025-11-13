#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include "../object.hpp"
#include "../tools/asset_manager.hpp"
#include "../utils/serializable.hpp"
#include "entity_registry.hpp"

namespace ducky::ecs {
class Level : public Object, public utils::Serializable {
 public:
  Level(std::string name = "level");
  void update_paths();
  void imgui_widget() override;

  void save(std::string path) override;
  void load(std::string path) override;

  std::string name = "level";

  std::string level_path;
  std::string content_path;

  std::vector<Entity*> entities;
};
}  // namespace ducky::ecs