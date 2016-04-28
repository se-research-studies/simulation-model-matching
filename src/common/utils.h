#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

namespace Common {

  namespace Utils {
    extern std::string removeBraces(std::string from);
    extern uint32_t stoui(const std::string& string);

    template<typename TargetInt, typename SourceInt>
    TargetInt to(SourceInt from) {
      TargetInt result = static_cast<TargetInt>(from);
      if (result != from) {
        throw std::out_of_range("Int type conversion error");
      }
      return result;
    }
  }

} // namespace Common

