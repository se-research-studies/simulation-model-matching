#include "utils.h"

namespace Common {

  std::string Utils::removeBraces(std::string from) {
    from.erase(0, 1);
    from.pop_back();
    return from;
  }

  uint32_t Utils::stoui(const std::string& string) {
    uint64_t longResult = std::stoul(string);
    uint32_t result = longResult;
    if (result != longResult) {
      throw std::out_of_range(string + " cannot be converted to uint32_t");
    }
    return result;
  }


} // namespace Common
