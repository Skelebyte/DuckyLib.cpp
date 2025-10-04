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
}

void CameraComponent::process() {
  this->view_ = Mat4::transformation(this->transform_->position,
                                     this->transform_->rotation,
                                     math::Vec3(1.0f, 1.0f, 1.0f));
  this->projection_.perspective(Mathf::to_radians(this->field_of_view),
                                window_->get_viewport_aspect(),
                                this->near_plane, this->far_plane);
}

Mat4& CameraComponent::get_projection() const {
  return (Mat4&)this->projection_;
}

Mat4& CameraComponent::get_view() const { return (Mat4&)this->view_; }