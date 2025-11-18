#pragma once

#include "../include/runtime_err.hpp"
#include "../third_party/Miniaudio/miniaudio.h"
#include "ecs/transform.hpp"

namespace ducky {
class AudioManager {
 public:
  static void init();
  static void shutdown();
  static ma_engine* get_engine();
  static bool stop_all;
  static bool pitch_with_timescale;

 private:
  static bool initialized_;
  static ma_engine* engine_;
  static ma_result result_;
};
}  // namespace ducky