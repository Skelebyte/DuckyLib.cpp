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

vec4 point_light() {
  vec3 n = normalize(normal);
  vec3 view_dir = normalize(camera_position - position);

  vec4 result = vec4(0.0);

  for (int i = 0; i < light_count; i++) {
    vec3 light_vec = lights[i].pos - position;
    float distance = length(light_vec);
    float a = 3.0;
    float b = 0.7;
    float point_intensity =
        1.0 / (a * distance * distance + b * distance + 1.0);
    vec3 light_dir = normalize(light_vec);

    float diffuse = max(dot(normal, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float specular = pow(max(dot(view_dir, reflect_dir), 0.0), 8);

    vec3 amb_res =
        ambient_strength * vec3(texture(diffuse_texture, texture_coord));
    vec3 dif_res = diffuse * vec3(texture(diffuse_texture, texture_coord));
    vec3 spec_res = specular_strength * specular *
                    vec3(texture(specular_texture, texture_coord));

    result += vec4(
        lights[i].color * (amb_res + dif_res * point_intensity * vec3(color) +
                           spec_res * point_intensity),
        1.0);
  }

  return result;
}

vec4 directional_light() {
  vec3 n = normalize(normal);
  vec3 view_dir = normalize(camera_position - position);

  vec4 result = vec4(0.0);

  for (int i = 0; i < light_count; i++) {
    vec3 light_dir = normalize(vec3(1.0, 1.0, 0.0));

    float diffuse = max(dot(normal, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float specular = pow(max(dot(view_dir, reflect_dir), 0.0), 8);

    vec3 amb_res =
        ambient_strength * vec3(texture(diffuse_texture, texture_coord));
    vec3 dif_res = diffuse * vec3(texture(diffuse_texture, texture_coord));
    vec3 spec_res = specular_strength * specular *
                    vec3(texture(specular_texture, texture_coord));

    result += vec4(
        lights[i].color * (amb_res + dif_res * vec3(color) + spec_res), 1.0);
  }

  return result;
}

vec4 spot_light() {
  vec3 n = normalize(normal);
  vec3 view_dir = normalize(camera_position - position);

  vec4 result = vec4(0.0);

  float outer_cone = 0.9;
  float inner_cone = 0.95;

  for (int i = 0; i < light_count; i++) {
    vec3 light_dir = normalize(lights[i].pos - position);

    float diffuse = max(dot(normal, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float specular = pow(max(dot(view_dir, reflect_dir), 0.0), 8);

    vec3 amb_res =
        ambient_strength * vec3(texture(diffuse_texture, texture_coord));
    vec3 dif_res = diffuse * vec3(texture(diffuse_texture, texture_coord));
    vec3 spec_res = specular_strength * specular *
                    vec3(texture(specular_texture, texture_coord));

    float angle = dot(vec3(0.0, -1.0, 0.0), -light_dir);
    float spot_intensity =
        clamp((angle - outer_cone) / (inner_cone - outer_cone), 0.0, 1.0);

    result += vec4(
        lights[i].color * (amb_res + dif_res * spot_intensity * vec3(color) +
                           spec_res * spot_intensity),
        1.0);
  }

  return result;
}

void main() { FragColor = point_light(); }