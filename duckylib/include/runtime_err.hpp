#pragma once

#include <functional>
#include <iostream>
#include <memory>

namespace ducky {
class RuntimeErr {
 public:
  static void throw_err(const std::string& message);
};
}  // namespace ducky