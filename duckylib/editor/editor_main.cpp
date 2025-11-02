#include "../ducky.hpp"

using namespace ducky;
using namespace ducky::ecs;
using namespace ducky::ecs::entities;
using namespace ducky::graphics;
using namespace ducky::math;
using namespace ducky::input;
using namespace ducky::tools;
using namespace ducky::utils;

int main(int argc, char** argv) {
  App app(argv[1]);
  Window window = Window("DuckyEngine", 1060, 800);

  Renderer::ambient_color = Vec3(1.0f, 0.3f, 0.3f);

  while (window.running()) {
    window.update();
    Renderer::clear_frame();

    window.swap();
  }
}