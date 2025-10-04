#include "../../include/math/mat4.hpp"

using namespace ducky;
using namespace ducky::math;

Mat4::Mat4(bool identity) {
  if (identity) {
    this->identity();
  } else {
    for (int i = 0; i < 16; i++) {
      this->data[i] = 0;
    }
  }
}
Mat4 Mat4::transformation(Vec3 pos, Vec3 rot, Vec3 sca,
                          Mat4_MultiplicationOrder order) {
  Mat4 result = Mat4();
  Mat4 position = Mat4();
  Mat4 rotation = Mat4();
  Mat4 scale = Mat4();
  position.Translate(pos);
  rotation.Rotate(rot);
  scale.Scale(sca);
  Mat4 half_matrix;
  switch (order) {
    case Mat4_TRS:
      half_matrix = rotation * scale;
      result = position * half_matrix;
      break;
    case Mat4_TSR:
      half_matrix = scale * rotation;
      result = position * half_matrix;
      break;
    case Mat4_RTS:
      half_matrix = position * scale;
      result = rotation * half_matrix;
      break;
    case Mat4_RST:
      half_matrix = scale * position;
      result = rotation * half_matrix;
      break;
    case Mat4_STR:
      half_matrix = position * rotation;
      result = scale * half_matrix;
      break;
    case Mat4_SRT:
      half_matrix = rotation * position;
      result = scale * half_matrix;
      break;
  }

  return result;
}

void Mat4::identity() {
  for (int i = 0; i < 16; i++)
    this->data[i] = 0;

  this->data[0] = 1;
  this->data[5] = 1;
  this->data[10] = 1;
  this->data[15] = 1;
}

void Mat4::Translate(Vec3 point) {
  this->data[12] = point.x;
  this->data[13] = point.y;
  this->data[14] = point.z;
}

void Mat4::Rotate(Vec3 angles) {
  Mat4 x_rot;
  Mat4 y_rot;
  Mat4 z_rot;

  Vec3 angles_in_rad =
      Vec3(angles.x * M_PI / 180, angles.y * M_PI / 180, angles.z * M_PI / 180);

  x_rot.data[5] = cos(angles_in_rad.x);
  x_rot.data[6] = -sin(angles_in_rad.x);
  x_rot.data[9] = sin(angles_in_rad.x);
  x_rot.data[10] = cos(angles_in_rad.x);
  y_rot.data[0] = cos(angles_in_rad.y);
  y_rot.data[2] = sin(angles_in_rad.y);
  y_rot.data[8] = -sin(angles_in_rad.y);
  y_rot.data[10] = cos(angles_in_rad.y);
  z_rot.data[0] = cos(angles_in_rad.z);
  z_rot.data[1] = sin(angles_in_rad.z);
  z_rot.data[4] = -sin(angles_in_rad.z);
  z_rot.data[5] = cos(angles_in_rad.z);
  Mat4 xy_rot = x_rot * y_rot;
  Mat4 xyz_rot = xy_rot * z_rot;
  Mat4 rot = *this * xyz_rot;
  for (int i = 0; i < 16; i++) {
    this->data[i] = rot.data[i];
  }
}

void Mat4::Scale(Vec3 scale) {
  this->data[0] = scale.x;
  this->data[5] = scale.y;
  this->data[10] = scale.z;
}

void Mat4::perspective(float fov_in_rads, float aspect, float near_plane,
                       float far_plane) {
  this->identity();
  this->data[0] = 1 / (aspect * tan(fov_in_rads / 2));
  this->data[5] = 1 / tan(fov_in_rads / 2);
  this->data[10] = -(far_plane + near_plane) / (far_plane - near_plane);
  this->data[11] = -1;
  this->data[14] = -(2 * far_plane * near_plane) / (far_plane - near_plane);
  this->data[15] = 0;
}

void Mat4::LookAt(Vec3 position, Vec3 target_position) {
  this->identity();
  Vec3 forward = (position - target_position).normalized();
  Vec3 right = Vec3::cross(Vec3(0.0f, 1.0f, 0.0f), forward).normalized();
  Vec3 up = Vec3::cross(forward, right);
  this->data[0] = right.x;
  this->data[4] = right.y;
  this->data[8] = right.z;
  this->data[12] = -Vec3::dot(right, position);
  this->data[1] = up.x;
  this->data[5] = up.y;
  this->data[9] = up.z;
  this->data[13] = -Vec3::dot(up, position);
  this->data[2] = forward.x;
  this->data[6] = forward.y;
  this->data[10] = forward.z;
  this->data[14] = -Vec3::dot(forward, position);
}

Mat4 Mat4::operator*(const Mat4& other) {
  Mat4 out;
  Mat4 current = *this;

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      float sum = 0;
      for (int i = 0; i < 4; i++) {
        sum += current.data[i * 4 + row] * other.data[col * 4 + i];
      }
      out.data[col * 4 + row] = sum;
    }
  }
  return out;
}

// void Identity(Mat4 mat4)
// {
//     for (int i = 0; i < 16; i++)
//         mat4[i] = 0;
//     mat4[0] = 1;
//     mat4[5] = 1;
//     mat4[10] = 1;
//     mat4[15] = 1;
// }
// void mat4_multiply(Mat4 out, Mat4 a, Mat4 b)
// {
//     Identity(out);
//     for (int row = 0; row < 4; row++)
//     {
//         for (int col = 0; col < 4; col++)
//         {
//             float sum = 0;
//             for (int i = 0; i < 4; i++)
//             {
//                 sum += a[i * 4 + row] * b[col * 4 + i];
//             }
//             out[col * 4 + row] = sum;
//         }
//     }
// }
// void Translate(Mat4 out, Vec3 point)
// {
//     out[12] = point.x;
//     out[13] = point.y;
//     out[14] = point.z;
// }
// void Rotate(Mat4 out, Vec3 angles)
// {
//     Mat4 x_rot;
//     Identity(x_rot);
//     Mat4 y_rot;
//     Identity(y_rot);
//     Mat4 z_rot;
//     Identity(z_rot);
//     Vec3 angles_in_rad = vec3(angles.x * M_PI / 180, angles.y * M_PI /180,
//     angles.z * M_PI / 180);
//     // for (int i = 0; i < 16; i++)
//     // {
//     //     x_rot[i] = mat4[i];
//     //     y_rot[i] = mat4[i];
//     //     z_rot[i] = mat4[i];
//     // }
//     x_rot[5] = cos(angles_in_rad.x);
//     x_rot[6] = -sin(angles_in_rad.x);
//     x_rot[9] = sin(angles_in_rad.x);
//     x_rot[10] = cos(angles_in_rad.x);
//     y_rot[0] = cos(angles_in_rad.y);
//     y_rot[2] = sin(angles_in_rad.y);
//     y_rot[8] = -sin(angles_in_rad.y);
//     y_rot[10] = cos(angles_in_rad.y);
//     z_rot[0] = cos(angles_in_rad.z);
//     z_rot[1] = sin(angles_in_rad.z);
//     z_rot[4] = -sin(angles_in_rad.z);
//     z_rot[5] = cos(angles_in_rad.z);
//     Mat4 xy_rot;
//     mat4_multiply(xy_rot, x_rot, y_rot);
//     Mat4 xyz_rot;
//     mat4_multiply(xyz_rot, xy_rot, z_rot);
//     Mat4 rot;
//     mat4_multiply(rot, out, xyz_rot);
//     for (int i = 0; i < 16; i++)
//     {
//         out[i] = rot[i];
//     }
// }
// void Scale(Mat4 out, Vec3 scale)
// {
//     out[0] = scale.x;
//     out[5] = scale.y;
//     out[10] = scale.z;
// }
// Mat4(Mat4 out, Vec3 pos, Vec3 rot, Vec3 sca, Mat4_MultiplicationOrder order)
// {
//     Identity(out);
//     Mat4 position;
//     Identity(position);
//     Mat4 rotation;
//     Identity(rotation);
//     Mat4 scale;
//     Identity(scale);
//     Translate(position, pos);
//     Rotate(rotation, rot);
//     Scale(scale, sca);
//     Mat4 half_matrix;
//     switch(order)
//     {
//         case Mat4_TRS:
//             mat4_multiply(half_matrix, rotation, scale);
//             mat4_multiply(out, position, half_matrix);
//             break;
//         case Mat4_TSR:
//             mat4_multiply(half_matrix, scale, rotation);
//             mat4_multiply(out, position, half_matrix);
//             break;
//         case Mat4_RTS:
//             mat4_multiply(half_matrix, position, scale);
//             mat4_multiply(out, rotation, half_matrix);
//             break;
//         case Mat4_RST:
//             mat4_multiply(half_matrix, scale, position);
//             mat4_multiply(out, rotation, half_matrix);
//             break;
//         case Mat4_STR:
//             mat4_multiply(half_matrix, position, rotation);
//             mat4_multiply(out, scale, half_matrix);
//             break;
//         case Mat4_SRT:
//             mat4_multiply(half_matrix, rotation, position);
//             mat4_multiply(out, scale, half_matrix);
//             break;
//         }
// }
// void mat4_perspective(Mat4 out, float fov_in_rads, float aspect, float
// near_plane, float far_plane)
// {
//     Identity(out);
//     out[0] = 1 / (aspect * tan(fov_in_rads / 2));
//     out[5] = 1 / tan(fov_in_rads / 2);
//     out[10] = -(far_plane + near_plane) / (far_plane - near_plane);
//     out[11] = -1;
//     out[14] = -(2 * far_plane * near_plane) / (far_plane - near_plane);
//     out[15] = 0;
// }
// void mat4_look_at(Mat4 out, Vec3 position, Vec3 targetPosition)
// {
//     Identity(out);
//     Vec3 forward = vec3_normalize(vec3_sub(position, targetPosition));
//     Vec3 right = vec3_normalize(vec3_cross(vec3(0.0f, 1.0f, 0.0f),forward));
//     Vec3 up = vec3_cross(forward, right);
//     out[0] = right.x;
//     out[4] = right.y;
//     out[8] = right.z;
//     out[12] = -vec3_dot(right, position);
//     out[1] = up.x;
//     out[5] = up.y;
//     out[9] = up.z;
//     out[13] = -vec3_dot(up, position);
//     out[2] = forward.x;
//     out[6] = forward.y;
//     out[10] = forward.z;
//     out[14] = -vec3_dot(forward, position);
// }
