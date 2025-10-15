#pragma once

#include "../../math/mat4.hpp"
#include "../../math/mathf.hpp"
#include "../../math/vec3.hpp"
#include "../../window.hpp"
#include "../components/transform.hpp"
#include "../entity.hpp"

namespace ducky {

namespace ecs {

namespace entities {

class Camera : public Entity {
 public:
  Camera(Window* window);
  void update() override;
  float field_of_view = 75.0f;
  float near_plane = 0.1f;
  float far_plane = 100.0f;
  math::Mat4 get_projection() const;
  math::Mat4 get_view() const;
  math::Vec3 get_orientation() const;

 private:
  Window* window_;
  math::Mat4 projection_;
  math::Mat4 view_;
  math::Vec3 orientation_;
};

}  // namespace entities

}  // namespace ecs

}  // namespace ducky