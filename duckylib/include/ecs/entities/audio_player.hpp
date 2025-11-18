#pragma once

#include "../../audio_manager.hpp"
#include "../../graphics/renderer.hpp"
#include "../../math/vec3.hpp"
#include "../../time.hpp"
#include "../../tools/asset_manager.hpp"
#include "../entity.hpp"
#include "camera.hpp"

namespace ducky::ecs::entities {
class AudioPlayer : public Entity {
 public:
  AudioPlayer(std::string audio_file_path, bool play_on_start = false,
              bool loop = false, bool is3D = false);
  ~AudioPlayer();
  void update() override;
  void imgui_widget() override;
  void play(bool from_beginning = true);
  void stop();
  bool is_playing() const;
  float volume = 1.0f;
  float pitch = 1.0f;
  float pan;
  bool loop;
  bool is3D;
  std::string path;

 private:
  ma_sound sound_;
  ma_result result_;
  ma_uint64 frame_;
  bool is_initialized_;
  bool playing_;
};
}  // namespace ducky::ecs::entities