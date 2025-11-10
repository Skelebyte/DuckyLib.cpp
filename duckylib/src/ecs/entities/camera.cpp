#include "../../../include/ecs/entities/camera.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::math;

Camera::Camera(Window* window) : Entity("camera", "camera") {
  this->window_ = window;
  this->view_ = Mat4();
  this->projection_ = Mat4();
  this->projection_.perspective(this->field_of_view,
                                window->get_viewport_aspect(), this->near_plane,
                                this->far_plane);
}

void Camera::update() { camera_update(); }

void Camera::camera_update() {
  this->view_.look_at(transform.position,
                      transform.position + transform.forward(),
                      transform.forward());

  this->projection_.perspective(Mathf::radians(this->field_of_view),
                                window_->get_viewport_aspect(),
                                this->near_plane, this->far_plane);
}

Mat4 Camera::get_projection() const { return this->projection_; }

Mat4 Camera::get_view() const { return this->view_; }

void Camera::imgui_widget() {
  transform.imgui_widget();
  ImGui::Text("Camera");
  ImGui::DragFloat("Field of View", &this->field_of_view, 0.1f, 1.0f, 179.0f);
  ImGui::DragFloat("Near Plane", &this->near_plane, 0.01f, 0.01f, 100.0f);
  ImGui::DragFloat("Far Plane", &this->far_plane, 1.0f, 1.0f, 1000.0f);
}