#pragma once

#include <cmath>
#include <stdexcept>
#include <string>

namespace Common {

    namespace Utils {
        extern std::string removeBraces(std::string from);
        extern uint32_t stoui(const std::string& string);
        extern std::string fileName(const std::string& filePath);

        template <typename TargetInt, typename SourceInt>
        TargetInt to(SourceInt from) {
            TargetInt result = static_cast<TargetInt>(from);
            if (result != from) {
                throw std::out_of_range("Type conversion error. From = " + std::to_string(from) + ", result = " + std::to_string(result));
            }
            return result;
        }

        // Returns 1 if a > b, 0 if a == b, -1 if a < b, limited to relevantDecimalPlaces
        template <typename T>
        int compare(T a, T b, int relevantDecimalPlaces = 4)
        {
            int scaleFactor = std::pow(10, relevantDecimalPlaces);
            int scaledA = a * scaleFactor;
            int scaledB = b * scaleFactor;
            if (scaledA > scaledB) {
                return 1;
            } else if (scaledA < scaledB) {
                return -1;
            } else {
                return 0;
            }
        }

    }

} // namespace Common

