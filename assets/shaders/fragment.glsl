#version 450 core
#define MAX_LIGHTS 8

struct Light {
  vec3 pos;
  vec3 color;
};
uniform int light_count;
uniform Light lights[MAX_LIGHTS];

out vec4 FragColor;

in vec2 texture_coord;
in vec3 normal;
in vec3 position;

uniform sampler2D tex0;
uniform vec3 camera_position;

void main() {
  vec3 n = normalize(normal);
  vec3 view_dir = normalize(camera_position - position);

  vec4 result = vec4(0.0);

  for (int i = 0; i < light_count; i++) {
    vec3 light_direction = normalize(lights[i].pos - position);

    float diffuse = max(dot(normal, light_direction), 0.0);
    vec3 reflect_dir = reflect(-light_direction, normal);
    float specular = pow(max(dot(view_dir, reflect_dir), 0.0), 8);

    float ambient = 0.2;
    float specular_strength = 0.5;

    result += vec4(
        lights[i].color * (ambient + diffuse + specular_strength * specular),
        1.0);
  }
  if (result == vec4(0.0)) {
    result = vec4(1.0);
  }

  // FragColor = texture(tex0, texture_coord);
  FragColor = texture(tex0, texture_coord) * result;
}