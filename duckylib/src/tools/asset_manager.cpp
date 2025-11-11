#include "../../include/tools/asset_manager.hpp"

using namespace ducky::utils;
using namespace ducky::tools;

DuckyAsset AssetManager::get(std::string path) {
  std::ifstream f = std::ifstream(path);
  nlohmann::json j = nlohmann::json::parse(f);
  f.close();
  return {j["path"], j["use_file"], j["data"]};
}

void AssetManager::pack(std::string path, DuckyAsset& asset) {
  nlohmann::json j;
  j["path"] = path;
  j["use_file"] = asset.use_file;
  j["data"] = asset.data;
  File::write(j.dump(), path, true);
}

bool AssetManager::is_path_valid(std::string path) {
  return std::filesystem::exists(path);
}