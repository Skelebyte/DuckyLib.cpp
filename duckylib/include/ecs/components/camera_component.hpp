#pragma once

#include "../../math/mat4.hpp"
#include "../../math/mathf.hpp"
#include "../../math/vec3.hpp"
#include "../../window.hpp"
#include "../component.hpp"
#include "transform.hpp"

namespace ducky {

namespace ecs {

namespace components {

class CameraComponent : public Component {
 public:
  CameraComponent(Transform* transform, Window* window);
  void process() override;
  float field_of_view = 75.0f;
  float near_plane = 0.1f;
  float far_plane = 100.0f;
  math::Mat4& get_projection() const;
  math::Mat4& get_view() const;

 private:
  Transform* transform_;
  Window* window_;
  math::Mat4 projection_;
  math::Mat4 view_;
};

}  // namespace components

}  // namespace ecs

}  // namespace ducky