#include "../include/time.hpp"

using namespace ducky;

float Time::time_scale = 1.0f;
float Time::delta_time_ = 0.0f;
float Time::processed_delta_time_ = 0.0f;
float Time::first_ = 0.0f;
float Time::last_ = 0.0f;
bool Time::is_render_frame_ = false;
float Time::target_fps_processed_ = 1.0f / 60.0f;
int Time::target_fps_ = 0;
float Time::frame_time_ = 0.0f;
int Time::fps_ = 0;
int Time::frame_count_ = 0;

float Time::delta_time() { return delta_time_ * time_scale; }

void Time::begin_frame() {
  is_render_frame_ = false;

  first_ = (float)SDL_GetTicks();

  delta_time_ = first_ - last_;

  last_ = first_;

  processed_delta_time_ += delta_time_;
  frame_time_ += delta_time_;

  while (processed_delta_time_ >= target_fps_processed_) {
    processed_delta_time_ -= target_fps_processed_;
    is_render_frame_ = true;

    if (frame_time_ >= 1000.0f) {
      frame_time_ = 0.0f;
      fps_ = frame_count_;
      frame_count_ = 0;
    }
  }

  if (is_render_frame_) {
    frame_count_++;
  }
}

void Time::set_target_fps(int fps) {
  target_fps_ = fps;
  target_fps_processed_ = 1.0f / (float)fps;
}

int Time::get_target_fps() { return target_fps_; }

bool Time::should_render_frame() { return is_render_frame_; }

int Time::fps() { return fps_; }