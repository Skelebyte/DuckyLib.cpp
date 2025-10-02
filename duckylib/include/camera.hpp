#pragma once

#include "math/mat4.hpp"
#include "math/mathf.hpp"
#include "math/vec3.hpp"

namespace ducky {
class Camera {
 public:
  Camera(float fov_in_degrees = 90.0f, float near_plane = 0.1f,
         float far_plane = 100.0f);
  math::Vec3 position;
  math::Vec3 rotation;
  math::Mat4 get_projection_matrix(float aspect) const;
  math::Mat4 get_view_matrix() const;

 private:
  math::Mat4 projection_matrix_;
  math::Mat4 view_matrix_;
  float fov_in_rads_;
  float near_plane_;
  float far_plane_;
};
}  // namespace ducky