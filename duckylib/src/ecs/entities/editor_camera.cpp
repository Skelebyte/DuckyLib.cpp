#include "../../../include/ecs/entities/editor_camera.hpp"

using namespace ducky::ecs::entities;
using namespace ducky::input;
using namespace ducky::math;

EditorCamera::EditorCamera(Window* window)
    : Camera(window),
      axis_horizontal(InputAxis(Keycode::D, Keycode::A)),
      axis_forward(InputAxis(Keycode::W, Keycode::S)),
      axis_vertical(InputAxis(Keycode::Q, Keycode::E)),
      look(Keycode::RMB),
      speed_up(Keycode::L_SHIFT) {
  last_mouse_ = Vec2(0, 0);
  first_mouse_ = true;
  name = "editor_camera";
}

void EditorCamera::update() {
  float current_speed = speed;

  if (Input::get_key(&speed_up)) {
    current_speed = speed * 2;
  }

  transform.position +=
      Vec3::cross(transform.forward(), transform.up()).normalized() *
          Input::get_axis(axis_horizontal) * current_speed *
          Time::delta_time() +
      transform.forward() * Input::get_axis(axis_forward) * current_speed *
          Time::delta_time() +
      transform.up() * Input::get_axis(axis_vertical) * current_speed *
          Time::delta_time();

  if (Input::get_key(&look)) {  // the rotation is in RADIANS for some reason.
    Input::cursor(*window_, true, false);
    Vec2 mouse = Input::get_mouse_position(*window_);

    if (first_mouse_) {
      last_mouse_ = mouse;
      first_mouse_ = false;
    }

    Vec2 mouse_delta = mouse;
    last_mouse_ = mouse;

    float x = (-mouse_delta.y / 10) * sensitivity * Time::delta_time();
    float y = (-mouse_delta.x / 10) * sensitivity * Time::delta_time();

    transform.rotation.x += Mathf::degrees(x);
    transform.rotation.y += Mathf::degrees(y);

    transform.rotation.x = std::clamp(transform.rotation.x, -1.57f, 1.57f);
  } else {
    Input::cursor(*window_, false, false);
    first_mouse_ = true;
  }

  camera_update();
}