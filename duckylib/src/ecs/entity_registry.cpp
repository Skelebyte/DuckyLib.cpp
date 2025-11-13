#include "../../include/ecs/entity_registry.hpp"

using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::utils;
using namespace ducky::graphics;

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

void EntityRegistry::create_entity_from_file(
    std::string path, std::vector<Entity*>* created_entities) {
  std::ifstream f = std::ifstream(path);
  nlohmann::json temp = nlohmann::json::parse(f);
  f.close();
  int entity_type =
      std::stoi(Serializable::static_get(path, "type_", "entity"));

  if (entity_type == EntityType::MESH_RENDERER) {
    MeshRenderer* mesh_renderer = new MeshRenderer(
        cube_vertices, sizeof(cube_vertices), cube_indices,
        sizeof(cube_indices),
        new Material(Texture(DEFAULT_TEXTURE), Texture(DEFAULT_TEXTURE),
                     Color::white()));
    mesh_renderer->load(path);
    created_entities->push_back(mesh_renderer);
  }

  if (entity_type == EntityType::CAMERA) {
    Camera* camera = new Camera();
    camera->load(path);
    created_entities->push_back(camera);
    Renderer::main_camera = camera;
  }

  if (entity_type == EntityType::EDITOR_CAMERA) {
    EditorCamera* editor_camera = new EditorCamera();
    editor_camera->load(path);
    created_entities->push_back(editor_camera);
    Renderer::main_camera = editor_camera;
  }

  if (entity_type == EntityType::POINT_LIGHT) {
    PointLight* point_light = new PointLight();
    point_light->load(path);
    created_entities->push_back(point_light);
  }

  if (entity_type == EntityType::SPOT_LIGHT) {
    SpotLight* spot_light = new SpotLight();
    spot_light->load(path);
    created_entities->push_back(spot_light);
  }

  if (entity_type == EntityType::DIRECTIONAL_LIGHT) {
    DirectionalLight* directional_light = new DirectionalLight();
    directional_light->load(path);
    created_entities->push_back(directional_light);
  }
}

void EntityRegistry::clear() {
  for (Entity* entity : entities_) {
    entity->destroy();
  }
  entities_.clear();

  Renderer::main_camera = nullptr;
  Renderer::point_lights.clear();
  Renderer::spot_lights.clear();
  Renderer::directional_lights.clear();
}