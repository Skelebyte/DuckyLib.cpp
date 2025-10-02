#version 450 core
// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the color from the Vertex Shader
in vec3 color;
in vec2 texture_coord;

uniform sampler2D tex0;

void main() {
  FragColor = texture(tex0, texture_coord);
  // stuiff
}