#include "../../../include/ecs/entities/camera.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::ecs::components;
using namespace ducky::math;

Camera::Camera(Window* window) : Entity("camera") {
  this->window_ = window;
  this->view_ = Mat4();
  this->projection_ = Mat4();
  this->projection_.perspective(this->field_of_view,
                                window->get_viewport_aspect(), this->near_plane,
                                this->far_plane);
}

void Camera::update() {
  this->view_.look_at(this->transform.position,
                      this->transform.position + this->transform.forward());

  this->projection_.perspective(Mathf::to_radians(this->field_of_view),
                                window_->get_viewport_aspect(),
                                this->near_plane, this->far_plane);
}

Mat4 Camera::get_projection() const { return this->projection_; }

Mat4 Camera::get_view() const { return this->view_; }
