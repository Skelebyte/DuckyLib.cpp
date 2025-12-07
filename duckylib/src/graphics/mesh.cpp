#include "../../include/graphics/mesh.hpp"

using namespace ducky::graphics;

Mesh::Mesh(std::string path) {
  vertices_.clear();
  indices_.clear();

  ufbx_load_opts options = {0};
  ufbx_error error;
  ufbx_scene* scene = ufbx_load_file(path.c_str(), &options, &error);
  if(!scene) {
    RuntimeErr::throw_err("Failed to load .fbx: " + path);
  }

  
  for(int i = 0; i < scene->nodes.count; i++) {
    ufbx_node* node = scene->nodes.data[i];
    if(node->is_root) continue;

    for(int i = 0; i < node->mesh->num_vertices; i++) {
          auto vec_x = node->mesh->vertex_position[i].x;
    auto vec_y = node->mesh->vertex_position[i].y;
    auto vec_z = node->mesh->vertex_position[i].z;
    vertices_.push_back(vec_x);
    vertices_.push_back(vec_y);
    vertices_.push_back(vec_z);
    auto uv_1 = node->mesh->vertex_uv[i].x;
    auto uv_2 = node->mesh->vertex_uv[i].y;
    vertices_.push_back(uv_1);
    vertices_.push_back(uv_2);
    auto normal_x = node->mesh->vertex_normal[i].x;
    auto normal_y = node->mesh->vertex_normal[i].y;
    auto normal_z = node->mesh->vertex_normal[i].z;
    vertices_.push_back(normal_x);
    vertices_.push_back(normal_y);
    vertices_.push_back(normal_z);

      

      
    }

    for(int i = 0; i < node->mesh->num_indices; i++) {
      indices_.push_back(node->mesh->vertex_indices[i]);
    }

    for(int i = 0; i < indices_.size(); i++) {
      std::cout<<indices_[i]<<", ";
    }

  }
}

std::vector<GLfloat> Mesh::get_vertices() const {
  return vertices_;
}

std::vector<GLuint> Mesh::get_indices() const {
  return indices_;
}