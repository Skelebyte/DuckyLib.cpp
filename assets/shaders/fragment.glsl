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

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;
uniform vec4 color;
uniform float specular_strength = 0.5;
uniform vec3 camera_position;
uniform float ambient_strength = 0.2;

void main() {
  vec3 n = normalize(normal);
  vec3 view_dir = normalize(camera_position - position);

  vec4 result = vec4(0.0);

  for (int i = 0; i < light_count; i++) {
    vec3 light_direction = normalize(lights[i].pos - position);

    float diffuse = max(dot(normal, light_direction), 0.0);
    vec3 reflect_dir = reflect(-light_direction, normal);
    float specular = pow(max(dot(view_dir, reflect_dir), 0.0), 8);

    vec3 amb_res =
        ambient_strength * vec3(texture(diffuse_texture, texture_coord));
    vec3 dif_res = diffuse * vec3(texture(diffuse_texture, texture_coord));
    vec3 spec_res = specular_strength * specular *
                    vec3(texture(specular_texture, texture_coord));

    result += vec4(
        lights[i].color * (amb_res + dif_res * vec3(color) + spec_res), 1.0);

    // result += vec4(
    //     lights[i].color * (ambient_strength + diffuse + specular_strength *
    //     specular), 1.0);
  }
  if (result == vec4(0.0)) {
    result = vec4(1.0);
  }

  // FragColor = texture(tex0, texture_coord);
  FragColor = result;
}