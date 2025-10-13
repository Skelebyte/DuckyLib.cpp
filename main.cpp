#include "duckylib/ducky.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::components;
using namespace ducky::graphics;
using namespace ducky::math;
using namespace ducky::input;

float sens = 10.0f;

int main(int argc, char** argv) {
  App app(argv[1]);
  Window window = Window("Hi mum!", 1000, 800);

  Renderer::init();

  Shader shader =
      Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

  Texture texture = Texture("assets/textures/frank.png");

  Entity camera = Entity("camera");
  CameraComponent* cam_comp =
      camera.add_component(new CameraComponent(&camera.transform, &window));
  cam_comp->near_plane = 0.01f;
  Entity mesh = Entity("mesh");
  MeshRenderer* mesh_mr = mesh.add_component(new MeshRenderer(
      &mesh.transform, cam_comp, pyramid_vertices, sizeof(pyramid_vertices),
      pyramid_indices, sizeof(pyramid_indices), &shader, texture));

  mesh.transform.position = Vec3(0.0f, -0.5f, -2.0f);

  InputAxis axis_horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis axis_vertical = InputAxis(Keycode::W, Keycode::S);
  InputAxis axis_up = InputAxis(Keycode::Q, Keycode::E);
  Keybind esc = Keybind(Keycode::ESC);
  Keybind look = Keybind(Keycode::LMB);
  bool cursor = false;

  Shader light_shader = Shader("assets/shaders/vertex_light.glsl",
                               "assets/shaders/fragment_light.glsl");

  Entity light = Entity("light");
  MeshRenderer* light_mr = light.add_component(new MeshRenderer(
      &light.transform, cam_comp, cube_vertices, sizeof(cube_vertices),
      cube_indices, sizeof(cube_indices), &light_shader, Texture()));
  light.transform.scale = Vec3(0.1f, 0.1f, 0.1f);

  std::cout << "Light shader: " << light_mr->shader_->id
            << " Mesh shader: " << mesh_mr->shader_->id << std::endl;

  Color light_color = Color::white();

  while (window.running()) {
    window.poll();

    Renderer::clear_frame();

    camera.update();

    mesh.update();
    light.update();

    camera.transform.position +=
        Vec3::cross(cam_comp->get_orientation(), camera.transform.up()) *
            Input::get_axis(axis_horizontal) * 0.01f +
        cam_comp->get_orientation() * Input::get_axis(axis_vertical) * 0.01f +
        camera.transform.up() * Input::get_axis(axis_up) * 0.01f;

    if (Input::get_key(look)) {
      Vec2 mouse = Input::get_mouse_position(window);
      Vec2i dimensions = window.get_dimensions();

      float x = -mouse.x * dimensions.x * sens;
      float y = mouse.y * dimensions.y * sens;

      camera.transform.rotation = Vec3(y, x, 0.0f);
      // Input::cursor(window, true, false);
    } else {
      Input::cursor(window, false, false);
    }

    window.render();
    // window.stop();
  }

  return 0;
}
