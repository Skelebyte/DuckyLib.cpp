#include "../../include/ecs/component.hpp"

using namespace ducky;
using namespace ducky::ecs;

Component::Component(unsigned int& entity_id) : entity_id_(entity_id) {}

Component::~Component() { entity_id_ = 0; }