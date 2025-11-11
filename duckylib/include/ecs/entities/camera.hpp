#pragma once

#include "../../math/mat4.hpp"
#include "../../math/mathf.hpp"
#include "../../math/vec3.hpp"
#include "../../window.hpp"
#include "../entity.hpp"
#include "../transform.hpp"

namespace ducky {

namespace ecs {

namespace entities {

class Camera : public Entity {
 public:
  Camera(Window* window);
  void update() override;
  float field_of_view = 75.0f;
  float near_plane = 0.1f;
  float far_plane = 100.0f;
  math::Mat4 get_projection() const;
  math::Mat4 get_view() const;
  void imgui_widget() override;
  void save(std::string path) override;
  void load(std::string path) override;

 protected:
  Window* window_;
  void camera_update();

 private:
  math::Mat4 projection_;
  math::Mat4 view_;
};

}  // namespace entities

}  // namespace ecs

}  // namespace ducky