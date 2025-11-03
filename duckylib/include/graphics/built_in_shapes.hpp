#pragma once

#include "../../third_party/glad/glad.h"
#include "mesh.hpp"

namespace ducky {

namespace graphics {

inline GLfloat pyramid_vertices[] = {
    // pos              // uv       // normal
    -0.5f, 0.0f, 0.5f,  0.0f, 0.0f, 0.0f,  -1.0f, 0.0f,  // bottom
    -0.5f, 0.0f, -0.5f, 0.0f, 5.0f, 0.0f,  -1.0f, 0.0f,  // bottom
    0.5f,  0.0f, -0.5f, 5.0f, 5.0f, 0.0f,  -1.0f, 0.0f,  // bottom
    0.5f,  0.0f, 0.5f,  5.0f, 0.0f, 0.0f,  -1.0f, 0.0f,  // bottom

    -0.5f, 0.0f, 0.5f,  0.0f, 0.0f, -0.8f, 0.5f,  0.0f,  // left
    -0.5f, 0.0f, -0.5f, 5.0f, 0.0f, -0.8f, 0.5f,  0.0f,  // left
    0.0f,  0.8f, 0.0f,  2.5f, 5.0f, -0.8f, 0.5f,  0.0f,  // left

    -0.5f, 0.0f, -0.5f, 5.0f, 0.0f, 0.0f,  0.5f,  -0.8f,  // back
    0.5f,  0.0f, -0.5f, 0.0f, 0.0f, 0.0f,  0.5f,  -0.8f,  // back
    0.0f,  0.8f, 0.0f,  2.5f, 5.0f, 0.0f,  0.5f,  -0.8f,  // back

    0.5f,  0.0f, -0.5f, 0.0f, 0.0f, 0.8f,  0.5f,  0.0f,  // right
    0.5f,  0.0f, 0.5f,  5.0f, 0.0f, 0.8f,  0.5f,  0.0f,  // right
    0.0f,  0.8f, 0.0f,  2.5f, 5.0f, 0.8f,  0.5f,  0.0f,  // right

    0.5f,  0.0f, 0.5f,  5.0f, 0.0f, 0.0f,  0.5f,  0.8f,  // front
    -0.5f, 0.0f, 0.5f,  0.0f, 0.0f, 0.0f,  0.5f,  0.8f,  // front
    0.0f,  0.8f, 0.0f,  2.5f, 5.0f, 0.0f,  0.5f,  0.8f   // front
};

inline GLuint pyramid_indices[] = {
    0,  1,  2,   // Bottom side
    0,  2,  3,   // Bottom side
    4,  6,  5,   // Left side
    7,  9,  8,   // Non-facing side
    10, 12, 11,  // Right side
    13, 15, 14   // Facing side
};

inline GLfloat cube_vertices[] = {
    // pos               // uv       // normal
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f,  // front
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f,  // front
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  // front
    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,  // front

    0.5f,  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  -1.0f,  // back
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f,  -1.0f,  // back
    -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  -1.0f,  // back
    0.5f,  0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  0.0f,  -1.0f,  // back

    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f,  0.0f,  // left
    -0.5f, -0.5f, 0.5f,  1.0f, 0.0f, -1.0f, 0.0f,  0.0f,  // left
    -0.5f, 0.5f,  0.5f,  1.0f, 1.0f, -1.0f, 0.0f,  0.0f,  // left
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -1.0f, 0.0f,  0.0f,  // left

    0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  // right
    0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,  // right
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  // right
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,  // right

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  -1.0f, 0.0f,  // bottom
    0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  -1.0f, 0.0f,  // bottom
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  -1.0f, 0.0f,  // bottom
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,  -1.0f, 0.0f,  // bottom

    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,  // top
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  // top
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  // top
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f   // top
};

inline GLuint cube_indices[] = {
    0,  1,  2,  0,  2,  3,   // front face CCW
    4,  5,  6,  4,  6,  7,   // back face CCW
    8,  9,  10, 8,  10, 11,  // left face CCW
    12, 13, 14, 12, 14, 15,  // right face CCW
    16, 17, 18, 16, 18, 19,  // bottom face CCW
    20, 21, 22, 20, 22, 23   // top face CCW
};

inline GLfloat plane_vertices[] = {
    // pos               // uv      // normal
    -0.5f, 0.0f, 0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom-left
    0.5f,  0.0f, 0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom-right
    0.5f,  0.0f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-right
    -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f   // top-left
};

inline GLuint plane_indices[] = {0, 1, 2, 0, 2, 3};

}  // namespace graphics

}  // namespace ducky