#pragma once

#include <iostream>
#include "../../third_party/glad/glad.h"
#include "../../third_party/stb/stb_image.h"
#include "../runtime_err.hpp"

// typedef enum DL_Blendmode { BM_NEAREST, BM_LINEAR } DL_Blendmode, Blendmode;

// typedef struct DL_Texture {
//   unsigned int id;
//   const char* path;
// } DL_Texture, Texture;

// unsigned char* dl_texture_generate(int width, int height, int r1, int g1,
//                                    int b1, int r2, int g2, int b2);
// int dl_texture_load(DL_Texture* texture, const char* path,
//                     DL_Blendmode blendmode);
// int dl_texture_data_load(DL_Texture* texture, unsigned char* data, int width,
//                          int height, DL_Blendmode blendmode);
// int dl_texture_bind(Texture* texture);

namespace ducky {

namespace graphics {

#define MISSING_TEXTURE "DUCKY_MISSING_TEXTURE"
#define EMPTY_TEXTURE "DUCKY_EMPTY_TEXTURE"
#define DEFAULT_TEXTURE "DUCKY_DEFAULT_TEXTURE"

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