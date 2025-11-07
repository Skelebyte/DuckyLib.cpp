#include "../include/app.hpp"

using namespace ducky;

App::App(const char* arg) {
  if (arg == "dev") {
    dev_mode_ = true;
  }

  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    RuntimeErr::throw_err("Failed to initialize SDL3: " +
                          std::string(SDL_GetError()));
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

  Time::set_target_fps(60);

  IMGUI_CHECKVERSION();
}

App::~App() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
  SDL_Quit();
}
