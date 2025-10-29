#include "../include/runtime_err.hpp"

using namespace ducky;

void RuntimeErr::throw_err(const std::string& message) {
  throw std::runtime_error(message);
}