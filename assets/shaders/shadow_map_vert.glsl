#version 330 core

layout(location = 0) in vec3 in_position;

uniform mat4 model;
uniform mat4 light_projection;

void main() { gl_Position = light_projection * model * vec4(in_position, 1.0); }