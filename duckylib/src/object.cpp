#include "../include/object.hpp"
#include "../include/object_registry.hpp"

using namespace ducky;

Object::Object() { id_ = ObjectRegistry::register_object(this); }

void Object::destroy() {
  if (this->destroyed)
    return;

  this->destroyed = true;
}

int Object::get_id() { return this->id_; }
