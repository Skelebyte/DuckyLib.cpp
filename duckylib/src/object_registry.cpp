#include "../include/object_registry.hpp"

using namespace ducky;

unsigned int ObjectRegistry::next_id_ = 0;
std::vector<Object*> ObjectRegistry::objects_;

unsigned int ObjectRegistry::register_object(Object* object) {
  unsigned int id = next_id_;
  next_id_++;

  objects_.push_back(object);

  return id;
}

std::vector<Object*>& ObjectRegistry::get_objects() { return objects_; }