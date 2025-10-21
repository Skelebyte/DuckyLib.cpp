#include "duckylib/ducky.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::components;
using namespace ducky::ecs::entities;
using namespace ducky::graphics;
using namespace ducky::math;
using namespace ducky::input;

float sens = 10.0f;

int main(int argc, char** argv) {
  App app(argv[1]);

  Window window = Window("Hi mum!", 1000, 800, false);

  RendererSettings settings = {0};
  settings.max_point_lights = 8;
  settings.max_spot_lights = 8;
  settings.max_directional_lights = 1;
  settings.culling_type = FaceCullingType::BACK;
  settings.enable_blending = true;
  settings.enable_culling = true;
  settings.enable_depth_test = true;
  settings.enable_line_smoothing = true;
  Renderer::init(settings);
  Renderer::ambient_strength = 0.5f;
  Renderer::ambient_color = Vec3(0.1f);

  Shader shader = Shader();

  Material crate = Material(Texture("assets/textures/container_diffuse.png"),
                            Texture("assets/textures/container_specular.png"),
                            Color::white());
  crate.specular_strength = 1.0f;

  Material frank = Material(Texture("assets/textures/frank.png"),
                            Texture(DEFAULT_TEXTURE_SPEC), Color::white());

  Camera camera = Camera(&window);

  MeshRenderer plane =
      MeshRenderer(&camera, plane_vertices, sizeof(plane_vertices),
                   plane_indices, sizeof(plane_indices), &shader, crate);
  plane.transform.position = Vec3(0.0f, -0.5f, -0.0f);
  plane.transform.scale = Vec3(10.0f, 1.0f, 10.0f);
  MeshRenderer cube =
      MeshRenderer(&camera, cube_vertices, sizeof(cube_vertices), cube_indices,
                   sizeof(cube_indices), &shader, crate);

  DirectionalLight sun = DirectionalLight();
  Renderer::add_light(&sun);
  // sun.transform.position = Vec3(0.0f, 2.0f, 0.0f);
  sun.transform.rotation = Vec3(1.0f, 0.5f, 0.0f);
  sun.intensity = 1.0f;
  sun.color = Color(0.98f, 0.94f, 0.8f, 1.0f);
  sun.enabled = false;

  SpotLight flashlight = SpotLight();
  Renderer::add_light(&flashlight);

  PointLight bulb = PointLight();
  Renderer::add_light(&bulb);
  bulb.transform.position = Vec3(2.5f, 1.0f, -2.3f);

  MeshRenderer bulb_mr =
      MeshRenderer(&camera, cube_vertices, sizeof(cube_vertices), cube_indices,
                   sizeof(cube_indices), &shader, frank);
  bulb_mr.transform = bulb.transform;
  bulb_mr.transform.scale = Vec3(0.1f);

  InputAxis axis_horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis axis_vertical = InputAxis(Keycode::W, Keycode::S);
  InputAxis axis_up = InputAxis(Keycode::Q, Keycode::E);
  Keybind esc = Keybind(Keycode::ESC);
  Keybind look = Keybind(Keycode::LMB);
  Keybind toggle_flashlight = Keybind(Keycode::F);
  Keybind toggle_bulb = Keybind(Keycode::SPACE);
  Keybind toggle_sun = Keybind(Keycode::L_ALT);
  bool cursor = false;

  while (window.running()) {
    window.poll();

    Renderer::clear_frame();

    camera.update();
    plane.update();
    cube.update();
    bulb_mr.update();

    flashlight.transform.position = camera.transform.position;
    flashlight.transform.rotation = camera.get_orientation();
    // sun.transform.rotation = camera.get_orientation();
    bulb.color = Color(1.0f, 0.5f, .9f, 1.0f);

    bulb_mr.transform.rotation += Vec3(0.05f);

    plane.transform.rotation.y += 0.1f;

    camera.transform.position +=
        Vec3::cross(camera.get_orientation(), camera.transform.up()) *
            Input::get_axis(axis_horizontal) * 0.01f +
        camera.get_orientation() * Input::get_axis(axis_vertical) * 0.01f +
        camera.transform.up() * Input::get_axis(axis_up) * 0.01f;

    if (Input::get_key(look)) {
      Vec2 mouse = Input::get_mouse_position(window);
      Vec2i dimensions = window.get_dimensions();

      float x = -mouse.x * dimensions.x * sens;
      float y = mouse.y * dimensions.y * sens;

      camera.transform.rotation = Vec3(y, x, 0.0f);

    } else {
      Input::cursor(window, false, false);
    }

    if (Input::get_key(toggle_bulb, true)) {
      bulb.enabled = !bulb.enabled;
    }
    if (Input::get_key(toggle_flashlight, true)) {
      flashlight.enabled = !flashlight.enabled;
    }

    if (Input::get_key(toggle_sun, true)) {
      sun.enabled = !sun.enabled;
    }

    window.render();
  }

  return 0;
}
