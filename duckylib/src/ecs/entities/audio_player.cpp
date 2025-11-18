#include "../../../include/ecs/entities/audio_player.hpp"

using namespace ducky::ecs::entities;
using namespace ducky::math;
using namespace ducky::graphics;
using namespace ducky::tools;

AudioPlayer::AudioPlayer(std::string path, bool play_on_start, bool loop,
                         bool is_3d)
    : Entity("audio_player", "audio_player") {
  this->path = path;
  this->loop = loop;
  this->is_3d = is_3d;

  result_ = ma_sound_init_from_file(AudioManager::get_engine(), path.c_str(), 0,
                                    NULL, NULL, &sound_);

  if (result_ != MA_SUCCESS) {
    std::cout << "failed to init sound: " << path << "\n";
    is_initialized_ = false;
  } else {
    is_initialized_ = true;
  }

  if (play_on_start) {
    play();
  }
}

AudioPlayer::~AudioPlayer() {
  if (is_initialized_) {
    ma_sound_uninit(&sound_);
  }
}

void AudioPlayer::update() {
  if (AudioManager::stop_all) {
    if (is_playing()) {
      stop();
    }
    return;
  }

  if (is_3d) {
    Vec3 pos = transform.position - Renderer::main_camera->transform.position;
    ma_sound_set_position(&sound_, pos.x, pos.y, pos.z);

    ma_engine_listener_set_direction(
        AudioManager::get_engine(), 0,
        Renderer::main_camera->transform.forward().x, 0,
        Renderer::main_camera->transform.forward().z);
  } else {
    ma_sound_set_position(&sound_, 0.0f, 0.0f, 0.0f);
    ma_engine_listener_set_direction(AudioManager::get_engine(), 0, 0, 0, 0);
  }

  frame_ = ma_sound_get_time_in_milliseconds(&sound_);

  if (loop && !is_playing()) {
    play(true);
  }

  ma_sound_set_volume(&sound_, volume);
  if (AudioManager::pitch_with_timescale) {
    ma_sound_set_pitch(&sound_, pitch * Time::time_scale);
  } else {
    ma_sound_set_pitch(&sound_, pitch);
  }
  ma_sound_set_pan(&sound_, pan);
}

void AudioPlayer::imgui_widget() {
  transform.imgui_widget();

  ImGui::Text(("Audio Player: " + name).c_str());
  ImGui::InputText("Audio File Path", (char*)path.c_str(), 256);
  ImGui::SameLine();
  if (ImGui::Button("Apply")) {
    if (!AssetManager::is_path_valid(path))
      return;
    stop();

    result_ = ma_sound_init_from_file(AudioManager::get_engine(), path.c_str(),
                                      0, NULL, NULL, &sound_);
    if (result_ != MA_SUCCESS) {
      RuntimeErr::throw_err("Failed to load sound: " + path);
    }
  }
  ImGui::Checkbox("Loop", &loop);
  ImGui::Checkbox("3D Sound", &is_3d);
  if (ImGui::Button("Play")) {
    play();
  }
  ImGui::SameLine();
  if (ImGui::Button("Stop")) {
    stop();
  }
  ImGui::Text(
      ("Is Playing: " + std::string(is_playing() ? "Yes" : "No")).c_str());

  ImGui::DragFloat("Volume", &volume, 0.1f, 0.0f, 2.0f);
  ImGui::DragFloat("Pitch", &pitch, 0.1f, 0.5f, 2.0f);
  ImGui::DragFloat("Pan", &pan, 0.1f, -1.0f, 1.0f);
}

void AudioPlayer::play(bool from_beginning) {
  if (!is_initialized_) {
    std::cout << "not init!\n";
    return;
  }
  if (frame_ != 0 && from_beginning) {
    ma_sound_set_start_time_in_milliseconds(&sound_, frame_);
  }

  result_ = ma_sound_start(&sound_);

  std::cout << result_ << "\n";

  if (result_ != MA_SUCCESS) {
    RuntimeErr::throw_err("Failed to play sound: " + path);
  }
  playing_ = true;
}

void AudioPlayer::stop() {
  if (!is_initialized_)
    return;

  result_ = ma_sound_stop(&sound_);
  if (result_ != MA_SUCCESS) {
    RuntimeErr::throw_err("Failed to stop sound: " + path);
  }
  playing_ = false;
}

bool AudioPlayer::is_playing() const {
  if (!is_initialized_)
    return false;

  if (ma_sound_is_playing(&sound_) == MA_TRUE) {
    return true;
  } else {
    return false;
  }
}

void AudioPlayer::save(std::string path) {
  add_entity_data();

  add("audio_file_path", this->path, "audio_player");
  add("volume", std::to_string(this->volume), "audio_player");
  add("pitch", std::to_string(this->pitch), "audio_player");
  add("pan", std::to_string(this->pan), "audio_player");
  add("loop", this->loop ? "true" : "false", "audio_player");
  add("is_3d", this->is_3d ? "true" : "false", "audio_player");

  write(path);
}

void AudioPlayer::load(std::string path) {
  load_entity_data(path);

  this->path = get(path, "audio_file_path", "audio_player");
  this->volume = std::stof(get(path, "volume", "audio_player"));
  this->pitch = std::stof(get(path, "pitch", "audio_player"));
  this->pan = std::stof(get(path, "pan", "audio_player"));
  this->loop = get(path, "loop", "audio_player") == "true" ? true : false;
  this->is_3d = get(path, "is_3d", "audio_player") == "true" ? true : false;

  stop();

  result_ = ma_sound_init_from_file(AudioManager::get_engine(),
                                    this->path.c_str(), 0, NULL, NULL, &sound_);

  if (result_ != MA_SUCCESS) {
    std::cout << "failed to init sound: " << this->path << "\n";
    is_initialized_ = false;
  } else {
    is_initialized_ = true;
  }
}