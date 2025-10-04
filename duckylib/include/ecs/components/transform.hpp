#pragma once

#include "../../math/vec3.hpp"
#include "../component.hpp"

namespace ducky {

namespace ecs {

namespace components {

class Transform : public Component {
 public:
  Transform();

 public:
  math::Vec3 position;
  math::Vec3 rotation;
  math::Vec3 scale;
};

}  // namespace components

}  // namespace ecs

}  // namespace ducky