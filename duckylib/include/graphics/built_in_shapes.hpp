#pragma once

#include "../../third_party/glad/glad.h"

namespace ducky {

namespace graphics {

inline GLfloat pyramid_vertices[] = {
    -0.5f, 0.0f, 0.5f,  5.0f, 5.0f,  // 0
    -0.5f, 0.0f, -0.5f, 5.0f, 0.0f,  // 1
    0.5f,  0.0f, -0.5f, 0.0f, 0.0f,  // 2
    0.5f,  0.0f, 0.5f,  5.0f, 0.0f,  // 3
    0.0f,  1.0f, 0.0f,  2.5f, 5.0f   // 4 (top)
};

inline GLuint pyramid_indices[] = {
    0, 1, 2, 0, 2, 3,  // base
    4, 1, 0,           // side 1
    4, 2, 1,           // side 2
    4, 3, 2,           // side 3
    4, 0, 3            // side 4
};

inline GLfloat cube_vertices[] = {
    // Front face
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // 0 front-bottom-left
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // 1 front-bottom-right
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    // 2 front-top-right
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   // 3 front-top-left

    // Back face
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f,   // 4 back-bottom-right
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // 5 back-bottom-left
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // 6 back-top-left
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f,    // 7 back-top-right

    // Left face
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // 8 left-bottom-back
    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // 9 left-bottom-front
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    // 10 left-top-front
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   // 11 left-top-back

    // Right face
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // 12 right-bottom-front
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // 13 right-bottom-back
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // 14 right-top-back
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f,    // 15 right-top-front

    // Bottom face
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // 16 bottom-back-left
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,   // 17 bottom-back-right
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    // 18 bottom-front-right
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // 19 bottom-front-left

    // Top face
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,  // 20 top-front-left
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // 21 top-front-right
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // 22 top-back-right
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f  // 23 top-back-left
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
    -0.5f, 0.0f, 0.5f,  0.0f, 1.0f,  // 0 bottom-left
    0.5f,  0.0f, 0.5f,  1.0f, 1.0f,  // 1 bottom-right
    0.5f,  0.0f, -0.5f, 1.0f, 0.0f,  // 2 top-right
    -0.5f, 0.0f, -0.5f, 0.0f, 0.0f   // 3 top-left
};

inline GLuint plane_indices[] = {0, 1, 2, 0, 2, 3};

}  // namespace graphics

}  // namespace ducky