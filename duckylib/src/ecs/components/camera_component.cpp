#include "../../../include/ecs/components/camera_component.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::components;
using namespace ducky::math;

CameraComponent::CameraComponent(Transform* transform, Window* window)
    : Component("CameraComponent") {
  this->transform_ = transform;
  this->window_ = window;
  this->view_ = Mat4();
  this->projection_ = Mat4();
  this->projection_.perspective(this->field_of_view,
                                window->get_viewport_aspect(), this->near_plane,
                                this->far_plane);
  this->orientation_ = Vec3(0, 0, -1);
}

void CameraComponent::process() {
  this->orientation_ = Vec3(0, 0, -1);
  Vec3 new_orientation = this->orientation_;
  new_orientation.rotate(Mathf::to_radians(this->transform_->rotation.x),
                         this->transform_->right());
  new_orientation.rotate(Mathf::to_radians(this->transform_->rotation.y),
                         this->transform_->up());
  new_orientation.rotate(Mathf::to_radians(this->transform_->rotation.z),
                         this->transform_->forward());

  this->orientation_ = new_orientation;

  this->view_.look_at(this->transform_->position,
                      this->transform_->position + this->orientation_);

  this->projection_.perspective(Mathf::to_radians(this->field_of_view),
                                window_->get_viewport_aspect(),
                                this->near_plane, this->far_plane);
}

Mat4 CameraComponent::get_projection() const { return this->projection_; }

Mat4 CameraComponent::get_view() const { return this->view_; }

Vec3 CameraComponent::get_orientation() const {
  Vec3 orientation = this->orientation_;
  return orientation;
}