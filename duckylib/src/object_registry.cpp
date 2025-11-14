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

void ObjectRegistry::clear() {
  next_id_ = 0;
  for (Object* obj : objects_) {
    if (obj->auto_register == false) {
      delete obj;
    } else {
      obj->register_object();
    }
  }
  objects_.shrink_to_fit();
}