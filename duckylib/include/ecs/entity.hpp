#pragma once

namespace ducky {

namespace ecs {
class Entity {
 public:
  Entity(unsigned int id);
  ~Entity();
  unsigned int get_id() const;

 private:
  unsigned int id_;
};
}  // namespace ecs

}  // namespace ducky