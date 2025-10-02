#pragma once

namespace ducky {
inline const char* vertex_shader_src =
    "#version 450 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "layout(location = 1) in vec3 aColor;\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "  color = aColor;\n"
    "}\0";

inline const char* fragment_shader_src =
    "#version 450 core\n"
    "out vec4 FragColor;\n"
    "in vec3 color;\n"
    "void main()\n"
    "{\n"
    "  FragColor = vec4(color, 1.0f);\n"
    "}\0";
}  // namespace ducky