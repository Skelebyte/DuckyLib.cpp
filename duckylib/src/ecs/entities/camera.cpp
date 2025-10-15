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
  this->orientation_ = Vec3(0, 0, -1);
}

void Camera::update() {
  this->orientation_ = Vec3(0, 0, -1);
  Vec3 new_orientation = this->orientation_;
  new_orientation.rotate(Mathf::to_radians(this->transform.rotation.x),
                         this->transform.right());
  new_orientation.rotate(Mathf::to_radians(this->transform.rotation.y),
                         this->transform.up());
  new_orientation.rotate(Mathf::to_radians(this->transform.rotation.z),
                         this->transform.forward());

  this->orientation_ = new_orientation;

  this->view_.look_at(this->transform.position,
                      this->transform.position + this->orientation_);

  this->projection_.perspective(Mathf::to_radians(this->field_of_view),
                                window_->get_viewport_aspect(),
                                this->near_plane, this->far_plane);
}

Mat4 Camera::get_projection() const { return this->projection_; }

Mat4 Camera::get_view() const { return this->view_; }

Vec3 Camera::get_orientation() const {
  Vec3 orientation = this->orientation_;
  return orientation;
}