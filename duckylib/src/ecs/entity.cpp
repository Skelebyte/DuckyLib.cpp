#include "../../include/ecs/entity.hpp"

using namespace ducky;
using namespace ducky::ecs;

Entity::Entity(unsigned int id) { this->id_ = id; }
Entity::~Entity() { this->id_ = 0; }

unsigned int Entity::get_id() const { return id_; }