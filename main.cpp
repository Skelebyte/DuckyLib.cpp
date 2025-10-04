#include "duckylib/include/app.hpp"
#include "duckylib/include/ecs/component.hpp"
#include "duckylib/include/ecs/components/camera_component.hpp"
#include "duckylib/include/ecs/components/mesh_renderer.hpp"
#include "duckylib/include/ecs/components/transform.hpp"
#include "duckylib/include/ecs/entity.hpp"
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

  Texture texture = Texture();

  Entity main_camera = Entity("camera");
  Transform* camera_transform = main_camera.add_component(new Transform());
  CameraComponent* camera =
      main_camera.add_component(new CameraComponent(camera_transform, &window));

  Entity pyramid = Entity("pyramid");
  Transform* pyramid_transform = pyramid.add_component(new Transform());
  MeshRenderer* mesh_renderer = pyramid.add_component(
      new MeshRenderer(pyramid_transform, camera, vertices, sizeof(vertices),
                       indices, sizeof(indices), shader, texture));

  pyramid_transform->position = Vec3(0.0f, -0.5f, -2.0f);

  while (window.running()) {
    window.poll();

    glClearColor(0.1, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pyramid_transform->rotation.y += 0.5f;

    main_camera.update();
    pyramid.update();

    window.render();
  }

  return 0;
}
