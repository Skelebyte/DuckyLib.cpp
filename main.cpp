#include "duckylib/include/app.hpp"
#include "duckylib/include/ecs/components/transform.hpp"
#include "duckylib/include/graphics/built_in_shaders.hpp"
#include "duckylib/include/graphics/ebo.hpp"
#include "duckylib/include/graphics/renderer.hpp"
#include "duckylib/include/graphics/shader.hpp"
#include "duckylib/include/graphics/texture.hpp"
#include "duckylib/include/graphics/vao.hpp"
#include "duckylib/include/graphics/vbo.hpp"
#include "duckylib/include/math/mat4.hpp"
#include "duckylib/include/math/mathf.hpp"
#include "duckylib/include/math/vec2.hpp"
#include "duckylib/include/math/vec3.hpp"
#include "duckylib/include/utils/file.hpp"
#include "duckylib/include/window.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::components;
using namespace ducky::graphics;
using namespace ducky::math;

int main() {
  float rot = 0.0f;

  App app;
  Window window = Window("Hi mum!", 600, 600);

  glViewport(0, 0, 600, 600);
  Renderer renderer = Renderer();
  // Vertices coordinates
  GLfloat vertices[] = {
      //     COORDINATES     /        COLORS      /   TexCoord  //
      -0.5f, 0.0f,  0.5f,  0.83f, 0.70f, 0.44f, 0.0f,  0.0f,  -0.5f, 0.0f,
      -0.5f, 0.83f, 0.70f, 0.44f, 5.0f,  0.0f,  0.5f,  0.0f,  -0.5f, 0.83f,
      0.70f, 0.44f, 0.0f,  0.0f,  0.5f,  0.0f,  0.5f,  0.83f, 0.70f, 0.44f,
      5.0f,  0.0f,  0.0f,  0.8f,  0.0f,  0.92f, 0.86f, 0.76f, 2.5f,  5.0f};

  GLuint indices[] = {0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};

  Shader shader =
      Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
  VAO vao;
  vao.init();
  vao.bind();
  VBO vbo;
  vbo.init(vertices, sizeof(vertices));
  EBO ebo;
  ebo.init(indices, sizeof(indices));

  vao.link_attribute(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  vao.link_attribute(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float),
                     (void*)(3 * sizeof(float)));
  vao.link_attribute(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float),
                     (void*)(6 * sizeof(float)));
  vao.unbind();
  vbo.unbind();
  ebo.unbind();

  Texture texture = Texture();
  GLuint uniform_id = glGetUniformLocation(shader.id, "scale");
  GLuint texture_uniform = glGetUniformLocation(shader.id, "tex0");
  shader.activate();
  glUniform1i(texture_uniform, 0);

  while (window.running()) {
    window.poll();

    glClearColor(0.1, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.activate();

    Mat4 model = Mat4::Transformation(
        Vec3(0.0f, 0.0f, -5.0f), Vec3(0.0f, rot, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
    Mat4 view = Mat4::Transformation(
        Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
    Mat4 projection = Mat4();
    projection.Perspective(Mathf::to_radians(60.0f),
                           window.get_viewport_aspect(), 0.1f, 100.0f);
    GLuint model_uniform = glGetUniformLocation(shader.id, "model");
    GLuint view_uniform = glGetUniformLocation(shader.id, "view");
    GLuint projection_uniform = glGetUniformLocation(shader.id, "projection");
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model.data);
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, view.data);
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, projection.data);
    glUniform1f(uniform_id, 0.5f);

    vao.bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT,
                   0);
    window.render();
    rot += 0.5f;
  }

  return 0;
}
