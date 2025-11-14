#include "../../include/ecs/level.hpp"

using namespace ducky::ecs;
using namespace ducky::utils;
using namespace ducky::tools;

Level::Level(std::string name) : Object() {
  this->name = name;
  level_path = "assets/levels/";
  content_path = "assets/levels/content/" + name + "/";
  auto_register = true;
}

void Level::update_paths() {
  level_path = "assets/levels/";
  content_path = "assets/levels/content/" + name + "/";
}

void Level::imgui_widget() {}

void Level::save(std::string path) {
  update_paths();

  if (!std::filesystem::exists(content_path)) {
    std::filesystem::create_directories(content_path);
  }

  for (const auto& entry : std::filesystem::directory_iterator(content_path)) {
    if (entry.path().extension() == ".json") {
      std::filesystem::remove(entry.path());
    }
  }

  for (Entity* e : EntityRegistry::get_entities()) {
    std::cout << "Saving entity: " << e->name << std::endl;
    std::string entity_path = content_path + e->name + ".json";
    e->save(entity_path);
    std::cout << "Save path: " << entity_path << std::endl;
  }

  add("content_path", content_path, "level");

  write(path + name + ".json");

  std::cout << "saved\n";
}

void Level::load(std::string path) {
  update_paths();

  EntityRegistry::clear();

  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    std::string file_name = entry.path().filename().string();
    if (!AssetManager::is_path_valid(path + file_name)) {
      std::cout << "Invalid path: " << path + file_name << std::endl;
      break;
    }

    EntityRegistry::create_entity_from_file(path + file_name);
  }
}