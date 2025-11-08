#pragma once

#include <SDL3/SDL.h>

namespace ducky {

class Time {
 public:
  static float delta_time();
  static void begin_frame();
  static float time_scale;
  static void set_target_fps(int fps);
  static int get_target_fps();
  static bool should_render_frame();
  static int fps();

 private:
  static float delta_time_;
  static float processed_delta_time_;
  static float first_;
  static float last_;
  static bool is_render_frame_;

  static int target_fps_;
  static float target_fps_processed_;
  static float frame_time_;
  static int fps_;
  static int frame_count_;
};

}  // namespace ducky