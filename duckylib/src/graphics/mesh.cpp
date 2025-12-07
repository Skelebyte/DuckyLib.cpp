#include "../../include/graphics/mesh.hpp"

using namespace ducky::graphics;

Mesh::Mesh(GLfloat vertices[], GLuint indices[]) {
  // vertices_ =
  //     std::vector<GLfloat>(vertices, sizeof(vertices) / sizeof(vertices[0]));
}

void Mesh::load(std::string path) {
  ufbx_load_opts options = {0};
  ufbx_error error;
  ufbx_scene* scene = ufbx_load_file(path.c_str(), &options, &error);
  if(!scene) {
    RuntimeErr::throw_err("Failed to load .fbx: " + path);
  }

  for(int i = 0; i < scene->nodes.count; i++) {
    ufbx_node* node = scene->nodes.data[i];
    if(node->is_root) continue;

    ufbx_vec3* v = node->mesh->vertex_position.values.data[i];
    vertices_.push_back((float)node->mesh->vertex_position.values.data.x);
  }


}