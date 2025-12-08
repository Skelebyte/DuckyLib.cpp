#include "../../include/graphics/mesh.hpp"

using namespace ducky::graphics;
using namespace ducky::utils;
using namespace ducky::math;

Mesh::Mesh(std::string path) {
  vertices_.clear();
  indices_.clear();

  FILE* file = fopen(path.c_str(), "r");

  if (file == NULL) {
    RuntimeErr::throw_err("Failed to read mesh: " + path);
  }

  while (1) {
    char line[128];
    int result = fscanf(file, "%s", line);
    if (result == EOF) {
      break;
    }
    if (strcmp(line, "vl") == 0) {
      fscanf(file, "%d\n", &vertices_length_);
    } else if (strcmp(line, "il") == 0) {
      fscanf(file, "%d\n", &indices_length_);
    } else if (strcmp(line, "vp") == 0) {
      Vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      vertices_.push_back(vertex.x);
      vertices_.push_back(vertex.y);
      vertices_.push_back(vertex.z);
    } else if (strcmp(line, "uv") == 0) {
      Vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y);
      vertices_.push_back(uv.x);
      vertices_.push_back(uv.y);
    } else if (strcmp(line, "nrm") == 0) {
      Vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      vertices_.push_back(normal.x);
      vertices_.push_back(normal.y);
      vertices_.push_back(normal.z);
    } else if (strcmp(line, "i") == 0) {
      int indice;
      fscanf(file, "%d\n", &indice);
      indices_.push_back(indice);
    }
  }
}

std::vector<GLfloat> Mesh::get_vertices() const { return vertices_; }

std::vector<GLuint> Mesh::get_indices() const { return indices_; }

int Mesh::get_vertices_length() const { return vertices_length_; }

int Mesh::get_indices_length() const { return indices_length_; }

/*

  ufbx_load_opts options = {0};
  ufbx_error error;
  ufbx_scene* scene = ufbx_load_file(path.c_str(), &options, &error);
  if (!scene) {
    RuntimeErr::throw_err("Failed to load .fbx: " + path);
  }

  for (int i = 0; i < scene->nodes.count; i++) {
    ufbx_node* node = scene->nodes.data[i];
    if (node->is_root)
      continue;

    for (int j = 0; j < node->mesh->num_vertices; j++) {
      auto vec_x = node->mesh->vertex_position[j].x;
      auto vec_y = node->mesh->vertex_position[j].y;
      auto vec_z = node->mesh->vertex_position[j].z;
      vertices_.push_back(vec_x);
      vertices_.push_back(vec_y);
      vertices_.push_back(vec_z);
      auto uv_1 = node->mesh->vertex_uv[j].x;
      auto uv_2 = node->mesh->vertex_uv[j].y;
      vertices_.push_back(uv_1);
      vertices_.push_back(uv_2);
      auto normal_x = node->mesh->vertex_normal[j].x;
      auto normal_y = node->mesh->vertex_normal[j].y;
      auto normal_z = node->mesh->vertex_normal[j].z;
      vertices_.push_back(normal_x);
      vertices_.push_back(normal_y);
      vertices_.push_back(normal_z);
    }

    for (int j = 0; j < node->mesh->num_indices; j++) {
      indices_.push_back(node->mesh->vertex_indices[j]);
    }
  }

*/

/*

  FILE* file = fopen(path.c_str(), "r");

  if (file == NULL) {
    RuntimeErr::throw_err("Failed to read mesh: " + path);
  }

  while (1) {
    char line[128];
    int res = fscanf(file, "%s", line);
    if (res == EOF) {
      break;
    }

    if (strcmp(line, "v") == 0) {
      Vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      vertices_.push_back(vertex.x);
      vertices_.push_back(vertex.y);
      vertices_.push_back(vertex.z);
    } else if (strcmp(line, "vt") == 0) {
      Vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y);
      vertices_.push_back(uv.x);
      vertices_.push_back(uv.y);
    } else if (strcmp(line, "vn") == 0) {
      Vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      vertices_.push_back(normal.x);
      vertices_.push_back(normal.y);
      vertices_.push_back(normal.z);
    } else if (strcmp(line, "f") == 0) {
      GLuint vertex_index[3], uv_index[3], normal_index[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                           &vertex_index[0], &uv_index[0], &normal_index[0],
                           &vertex_index[1], &uv_index[1], &normal_index[1],
                           &vertex_index[2], &uv_index[2], &normal_index[2]);
      if (matches != 9) {
        RuntimeErr::throw_err("Failed to parse face in mesh: " + path);
      }
      // OBJ file indices start at 1, so we need to subtract 1
      indices_.push_back(vertex_index[0] - 1);
      indices_.push_back(vertex_index[1] - 1);
      indices_.push_back(vertex_index[2] - 1);
    }
  }

*/