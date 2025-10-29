#pragma once

#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace ducky::utils {

class File {
 public:
  static std::string read(std::string path);
  static void write(std::string content, std::string path,
                    bool overwrite = false);
};

}  // namespace ducky::utils