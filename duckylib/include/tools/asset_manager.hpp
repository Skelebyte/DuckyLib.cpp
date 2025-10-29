#pragma once
#include <fstream>
#include <iostream>
#include "../../third_party/json.hpp/json.hpp"
#include "../utils/file.hpp"

namespace ducky::tools {

struct DuckyAsset {
  std::string path_to_asset;
  bool use_file;
  std::string data;
};

class AssetManager {
 public:
  static DuckyAsset get(std::string path);
  static void pack(std::string path, DuckyAsset& asset);
};

}  // namespace ducky::tools