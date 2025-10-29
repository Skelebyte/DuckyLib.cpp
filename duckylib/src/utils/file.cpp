#include "../../include/utils/file.hpp"

using namespace ducky::utils;

std::string File::read(std::string path) {
  std::ifstream file;

  file.open(path, std::ios::binary | std::ios::ate);

  if (file.fail()) {
    return NULL;
  }
  std::streamsize size = (std::streamsize)file.tellg();
  file.seekg(0, std::ios::beg);
  char* buffer = new char[size + 1];
  if (!file.read(buffer, size)) {
    delete[] buffer;
    return NULL;
  }
  buffer[size] = '\0';

  file.close();

  return buffer;
}

void File::write(std::string value, std::string path, bool overwrite) {
  std::ofstream file;

  if (overwrite) {
    file.open(path, std::ios::trunc);
  } else {
    file.open(path, std::ios::app);
  }

  file << value << std::endl;
  file.close();
}