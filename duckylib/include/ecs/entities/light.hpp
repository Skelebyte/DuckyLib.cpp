#pragma once

#include <iostream>
#include "../../graphics/color.hpp"
#include "../../graphics/shader.hpp"
#include "../entity.hpp"

namespace ducky {

namespace ecs {

namespace entities {

class Light : public Entity {
 public:
  Light(graphics::Shader* shader);
  ~Light();
  graphics::Color color = graphics::Color::white();

 private:
  graphics::Shader* shader_;
};
}  // namespace entities

}  // namespace ecs

}  // namespace ducky