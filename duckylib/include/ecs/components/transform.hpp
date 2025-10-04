#pragma once

#include "../../math/vec3.hpp"
#include "../component.hpp"

namespace ducky {

namespace ecs {

namespace components {

class Transform : public Component {
 public:
  Transform();
  Transform(math::Vec3 pos, math::Vec3 rot, math::Vec3 sca);

  void process() override;

 public:
  math::Vec3 position;
  math::Vec3 rotation;
  math::Vec3 scale;
};

}  // namespace components

}  // namespace ecs

}  // namespace ducky