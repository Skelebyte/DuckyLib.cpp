#include <filesystem>
#define DUCKY_USE_NAMESPACES
#define DUCKY_ALLOW_ENGINE_KEYBINDS
#include "duckylib/ducky.hpp"
#include "duckylib/include/editor.hpp"

int main(int argc, char** argv) {
  App app(argv[1]);
  Window window("Ducky Editor v1.0", 1000, 800);

  Renderer::ambient_color = Vec3(1.0f);

  Renderer::main_shader = new Shader();

  Level current_level = Level("base_level");

  Renderer::main_camera = new EditorCamera();

  DirectionalLight* sun = new DirectionalLight();
  sun->name = "sun";
  sun->transform.rotation = Vec3(1.0f);

  float font_size = 16.0f;
  char* font_path =
      (char*)"assets/fonts/Roboto_Mono/RobotoMono-VariableFont_wght.ttf";

  AudioPlayer* background_music =
      new AudioPlayer("assets/sounds/fanatica.wav", false, false);

  ImFont* font = window.io->Fonts->AddFontFromFileTTF(font_path, font_size);
  window.io->Fonts->Build();
  window.io->FontDefault = font;

  while (window.running()) {
    window.update();
    ducky_engine_keybinds();
    Renderer::clear_frame();
    EntityRegistry::update();

    Editor::update(current_level);

    window.swap();
  }

  EntityRegistry::clear();
}
