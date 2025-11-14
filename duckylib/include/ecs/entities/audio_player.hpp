#pragma once

#define MINIAUDIO_IMPLEMENTATION
#include "../../../third_party/Miniaudio/miniaudio.h"
#include "../entity.hpp"

namespace ducky::ecs::entities {
class AudioPlayer : public Entity {
 public:
  AudioPlayer(std::string audio_file_path, bool loop = false);
  ~AudioPlayer();
  void play();
  void pause();
  void stop();
  bool is_playing() const;
  bool looping;

 private:
  ma_engine engine;
  ma_sound sound;
  bool is_initialized;
};
}  // namespace ducky::ecs::entities