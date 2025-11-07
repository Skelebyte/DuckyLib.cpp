#pragma once

#include <iostream>
#include "pi.hpp"
#include "vec3.hpp"

namespace ducky {

namespace math {

typedef enum Mat4_MultiplicationOrder {
  Mat4_TRS,  // `entity` default (`transform * (rotation * scale)`)
  Mat4_TSR,  // `ui_entity` default (`transform * (scale * rotation)`)
  Mat4_RST,  // `rotation * (scale * transform)`
  Mat4_RTS,  // `rotation * (transform * scale)`
  Mat4_SRT,  // `scale * (rotation * transform)`
  Mat4_STR,  // `scale * (transform * rotation)`
} Mat4_MultiplicationOrder,
    MultiplicationOrder;

class Mat4 {
 public:
  float data[16];
  Mat4(bool identity = true);
  static Mat4 transformation(Vec3 pos, Vec3 rot, Vec3 sca,
                             Mat4_MultiplicationOrder order = Mat4_TRS);
  void identity();

  void translate(Vec3 point);
  void rotate(Vec3 angles);
  void scale(Vec3 scale);

  void perspective(float fov_in_rads, float aspect, float near_plane,
                   float far_plane);
  void look_at(Vec3 position, Vec3 target_position, Vec3 forward);

  Mat4 inverse() const;

  Mat4 operator*(const Mat4& other);
};

}  // namespace math

// typedef float Mat4[16];

// /**
//  * @brief Default value for a 4x4 matrix.
//  * @code {.c}
//  * 1, 0, 0, 0,
//  * 0, 1, 0, 0,
//  * 0, 0, 1, 0,
//  * 0, 0, 0, 1,
//  * @endcode
//  */

}  // namespace ducky
