#pragma once

#include <cstdint>
#include <string>

namespace Common {

  namespace Utils {
    extern std::string removeBraces(std::string from);
    extern uint32_t stoui(const std::string& string);
  }

} // namespace Common

