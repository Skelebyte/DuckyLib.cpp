#pragma once

#include "../math/mathf.hpp"
#include "../math/vec3.hpp"
#include "../object.hpp"

namespace ducky {

namespace ecs {

class Transform : public Object {
 public:
  Transform();
  Transform(math::Vec3 pos, math::Vec3 rot, math::Vec3 sca);
  math::Vec3 forward() const;
  math::Vec3 right() const;
  math::Vec3 up() const;
  void process();
  void imgui_widget() override;

 public:
  math::Vec3 position;
  math::Vec3 rotation;
  math::Vec3 scale;
};
}  // namespace ecs

}  // namespace ducky