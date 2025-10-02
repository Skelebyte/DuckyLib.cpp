#include "../../include/utils/file.hpp"

using namespace ducky;

std::string File::read(std::string path) {
  // Debug debug;
  std::ifstream file;

  file.open(path, std::ios::binary | std::ios::ate);

  if (file.fail()) {
    // debug.log("Failed to read file: " + path + ".", Severity::ERROR);
    return NULL;
  }
  std::streamsize size = (std::streamsize)file.tellg();
  file.seekg(0, std::ios::beg);
  char* buffer = new char[size + 1];
  if (!file.read(buffer, size)) {
    // debug.log("Failed to read file from path: " + path + ".",
    // Severity::ERROR);
    delete[] buffer;
    return NULL;
  }
  buffer[size] = '\0';

  file.close();

  return buffer;
}

void File::write(std::string value, std::string path) {
  std::ofstream file;

  file.open(path, std::ios::app);
  file << value << std::endl;
  file.close();
}