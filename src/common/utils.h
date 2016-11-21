#pragma once

#include <cmath>
#include <stdexcept>
#include <string>

namespace Common {

    namespace Utils {
        extern std::string removeBraces(std::string from);
        extern std::string fileName(const std::string& filePath);
        extern std::string fileFolderPath(const std::string& filePath);

        // Converts an int value of type SourceInt to type TargetInt. Used to remove warnings
        template <typename TargetInt, typename SourceInt>
        TargetInt to(SourceInt from) {
            TargetInt result = static_cast<TargetInt>(from);
            return result;
        }

        // Converts a string to an int of type TargetInt. Unlike std::stoi this method can be used for unsigned types as well
        template <typename TargetInt>
        TargetInt stoi(const std::string& string) {
            uint64_t longResult = std::stoul(string);
            TargetInt result = Utils::to<TargetInt>(longResult);
            if (result != longResult) {
                throw std::out_of_range(string + " cannot be converted to uint32_t");
            }
            return result;
        }

        // Returns 1 if a > b, 0 if a == b, -1 if a < b, limited in precision to relevantDecimalPlaces
        template <typename T>
        int compare(T a, T b, int relevantDecimalPlaces = 4) {
            int scaleFactor = to<int>(std::pow(10, relevantDecimalPlaces));
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

        // Inspired by boost::hash_combine
        template <class T>
        size_t hashCombine(size_t currentHash, const T& newValue) {
            std::hash<T> hasher;
            size_t result = currentHash;
            result ^= hasher(newValue) + 0x9e3779b9 + (result<<6) + (result>>2);
            return result;
        }

    }

} // namespace Common

