#include "../include/audio_manager.hpp"

using namespace ducky;

bool AudioManager::stop_all = false;
bool AudioManager::pitch_with_timescale = true;
bool AudioManager::initialized_ = false;
ma_engine* AudioManager::engine_ = nullptr;
ma_result AudioManager::result_ = MA_SUCCESS;

void AudioManager::init() {
  if (!initialized_) {
    engine_ = new ma_engine();
    result_ = ma_engine_init(NULL, engine_);
    if (result_ != MA_SUCCESS) {
      RuntimeErr::throw_err("Failed to initialize audio engine.");
    }
    initialized_ = true;
  }
}

void AudioManager::shutdown() {
  if (initialized_) {
    ma_engine_uninit(engine_);
  }
}

ma_engine* AudioManager::get_engine() { return engine_; }
