#define STB_IMAGE_IMPLEMENTATION
#include "../../include/graphics/texture.hpp"

using namespace ducky;
using namespace ducky::graphics;

static unsigned char* graphics::custom_texture(int width, int height, int r1,
                                               int g1, int b1, int r2, int g2,
                                               int b2) {
  unsigned char* data = (unsigned char*)malloc(width * height * 3);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float t = (float)x / width;
      float s = (float)y / height;

      int index = (y * width + x) * 3;
      if (((int)(s * height) + (int)(t * width)) % 2 == 0) {
        data[index] = r1;
        data[index + 1] = g1;
        data[index + 2] = b1;
      } else {
        data[index] = r2;
        data[index + 1] = g2;
        data[index + 2] = b2;
      }
    }
  }

  return data;
}

Texture::Texture(std::string path, Blendmode blendmode) {
  this->path = (char*)path.c_str();
  stbi_set_flip_vertically_on_load(1);

  bool load_success = false;
  bool is_ducky_texture = false;

  int width, height, channel_count;

  unsigned char* data;

  if (path != MISSING_TEXTURE && path != EMPTY_TEXTURE_WHITE &&
      path != DEFAULT_TEXTURE && path != DEFAULT_TEXTURE_SPEC &&
      path != EMPTY_TEXTURE_BLACK) {
    data = stbi_load(path.c_str(), &width, &height, &channel_count, 0);
  } else {
    is_ducky_texture = true;
  }

  if (data && !is_ducky_texture) {
    load_success = true;
  } else {
    load_success = false;
  }

  glGenTextures(1, &this->id);
  Renderer::get_gl_error("Texture : glGenTextures");

  glBindTexture(GL_TEXTURE_2D, this->id);
  Renderer::get_gl_error("Texture : glBindTextures");

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  Renderer::get_gl_error("Texture : glTexParameteri(GL_TEXTURE_WRAP_S, ...)");

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  Renderer::get_gl_error("Texture : glTexParameteri(GL_TEXTURE_WRAP_T, ...)");

  if (path != MISSING_TEXTURE && path != EMPTY_TEXTURE_WHITE &&
      path != DEFAULT_TEXTURE && load_success == true &&
      path != EMPTY_TEXTURE_BLACK && !is_ducky_texture) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    blendmode == LINEAR ? GL_LINEAR : GL_NEAREST);
    Renderer::get_gl_error(
        "Texture : glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ...)");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    blendmode == LINEAR ? GL_LINEAR : GL_NEAREST);
    Renderer::get_gl_error(
        "Texture : glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ...)");

  } else {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    Renderer::get_gl_error(
        "Texture : glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, "
        "GL_NEAREST)");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    Renderer::get_gl_error(
        "Texture : glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, "
        "GL_NEAREST)");
  }

  if (load_success) {
    GLenum format = channel_count == 4 ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    Renderer::get_gl_error("Texture : glTexImage2D");
    glGenerateMipmap(GL_TEXTURE_2D);
    Renderer::get_gl_error("Texture : glGenerateMipmap");
    free(data);
  } else {
    data = custom_texture(4, 4, 255, 0, 255, 0, 0, 0);
    if (!data) {
      RuntimeErr::throw_err("Failed to generate missing texture");
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 data);
    Renderer::get_gl_error("Texture : glTexImage2D");
    glGenerateMipmap(GL_TEXTURE_2D);
    Renderer::get_gl_error("Texture : glGenerateMipmap");
    free(data);
  }

  if (is_ducky_texture) {
    width = 4;
    height = 4;

    if (path == MISSING_TEXTURE) {
      data = custom_texture(width, height, 255, 0, 255, 0, 0, 0);
      if (!data) {
        RuntimeErr::throw_err("Failed to generate missing texture");
      }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      free(data);
      return;
    }

    if (path == EMPTY_TEXTURE_WHITE) {
      data = custom_texture(width, height, 255, 255, 255, 255, 255, 255);
      if (!data) {
        RuntimeErr::throw_err("Failed to generate empty texture");
      }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      free(data);
      return;
    }

    if (path == EMPTY_TEXTURE_BLACK) {
      data = custom_texture(width, height, 0, 0, 0, 0, 0, 0);
      if (!data) {
        RuntimeErr::throw_err("Failed to generate empty texture");
      }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      free(data);
      return;
    }

    if (path == DEFAULT_TEXTURE) {
      data = custom_texture(width, height, 255, 255, 255, 150, 150, 150);
      if (!data) {
        RuntimeErr::throw_err("Failed to generate default texture");
      }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      free(data);
      return;
    }
    if (path == DEFAULT_TEXTURE_SPEC) {
      data = custom_texture(width, height, 0, 0, 0, 0, 0, 0);
      if (!data) {
        RuntimeErr::throw_err("Failed to generate default texture");
      }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      free(data);
      return;
    }
  }
}

Texture::Texture(unsigned char* data, int width, int height,
                 Blendmode blendmode) {
  if (data == nullptr) {
    RuntimeErr::throw_err("Failed to load texture data");
  }

  glGenTextures(1, &this->id);
  glBindTexture(GL_TEXTURE_2D, this->id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  blendmode == LINEAR ? GL_LINEAR : GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  blendmode == LINEAR ? GL_LINEAR : GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  free(data);
}

void Texture::bind() {
  glBindTexture(GL_TEXTURE_2D, this->id);
  Renderer::get_gl_error();
}
void Texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

bool Texture::is_valid() const { return valid_; }