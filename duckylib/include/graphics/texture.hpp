#pragma once

#include <iostream>
#include "../../third_party/glad/glad.h"
#include "../../third_party/stb/stb_image.h"
#include "../runtime_err.hpp"
#include "../tools/asset_manager.hpp"
#include "renderer.hpp"

namespace ducky {

namespace graphics {

#define MISSING_TEXTURE "DUCKY_MISSING_TEXTURE"
#define EMPTY_TEXTURE "DUCKY_EMPTY_TEXTURE"
#define DEFAULT_TEXTURE "DUCKY_DEFAULT_TEXTURE"
#define DEFAULT_TEXTURE_SPEC "DUCKY_DEFAULT_TEXTURE_SPEC"

enum Blendmode { NEAREST, LINEAR };

static unsigned char* custom_texture(int width, int height, int r1, int g1,
                                     int b1, int r2, int g2, int b2);

class Texture {
 public:
  Texture(std::string path = DEFAULT_TEXTURE, Blendmode blendmode = LINEAR);
  Texture(unsigned char* data, int width, int height,
          Blendmode blendmode = LINEAR);
  void bind();
  void unbind();
  GLuint id;
  const char* path;
};

}  // namespace graphics

}  // namespace ducky