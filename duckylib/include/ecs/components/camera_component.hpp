#pragma once

#include "../../math/vec3.hpp"
#include "../component.hpp"

namespace ducky {

namespace ecs {

namespace components {

class CameraComponent : public Component {
 public:
  CameraComponent();
};

}  // namespace components

}  // namespace ecs

}  // namespace ducky