#include "../../../include/ecs/entities/editor_camera.hpp"

using namespace ducky::ecs::entities;
using namespace ducky::input;
using namespace ducky::math;
using namespace ducky::graphics;

EditorCamera::EditorCamera()
    : Camera(),
      axis_horizontal(InputAxis(Keycode::D, Keycode::A)),
      axis_forward(InputAxis(Keycode::W, Keycode::S)),
      axis_vertical(InputAxis(Keycode::Q, Keycode::E)),
      look(Keycode::RMB),
      speed_up(Keycode::L_SHIFT),
      slow_down(Keycode::L_CTRL) {
  last_mouse_ = Vec2(0, 0);
  first_mouse_ = true;
  name = "editor_camera";
  type_ = EntityType::EDITOR_CAMERA;
}

void EditorCamera::update() {
  float current_speed = speed;

  if (Input::get_key(&speed_up)) {
    current_speed = speed * 2;
  }

  if (Input::get_key(&slow_down)) {
    current_speed = speed / 2;
  }

  if (can_move_) {
    transform.position +=
        Vec3::cross(transform.forward(), transform.up()).normalized() *
            Input::get_axis(axis_horizontal) * current_speed *
            Time::delta_time() +
        transform.forward() * Input::get_axis(axis_forward) * current_speed *
            Time::delta_time() +
        transform.up() * Input::get_axis(axis_vertical) * current_speed *
            Time::delta_time();
  }

  if (Input::get_key(&look)) {  // the rotation is in RADIANS for some reason.
    can_move_ = true;
    Input::cursor(*Renderer::main_window, true, true);
    Vec2 mouse = Input::get_mouse_position(*Renderer::main_window);

    if (first_mouse_) {
      mouse = Input::get_mouse_position(*Renderer::main_window);
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
    Input::cursor(*Renderer::main_window, false, false);
    first_mouse_ = true;
    can_move_ = false;
  }

  camera_update();
}

void EditorCamera::imgui_widget() {
  Camera::imgui_widget();
  ImGui::Text("Editor Camera");
  ImGui::DragFloat("Sensitivity", &this->sensitivity, 0.0001f, 0.0001f, 0.01f);
  ImGui::DragFloat("Speed", &this->speed, 0.001f, 0.001f, 100.0f);
}
