#include "../../include/utils/to_string.hpp"

using namespace ducky::utils;

std::string farr(float arr[], unsigned int len) {
  std::string result;
  result.append("[");
  for (int i = 0; i < len; i++) {
    result.append(std::to_string(arr[i]));
    if (i < len - 1) {
      result.append(",");
    } else {
      result.append("]");
    }
  }

  return result;
}