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

    std::string Utils::fileName(const std::string& filePath)
    {
        size_t lastSlash = filePath.find_last_of("/");
        if (lastSlash == std::string::npos) {
            return filePath;
        } else {
            return filePath.substr(lastSlash + 1, std::string::npos);
        }
    }

    std::string Utils::fileFolderPath(const std::string& filePath)
    {
        size_t lastSlash = filePath.find_last_of("/");
        if (lastSlash == std::string::npos) {
            return filePath;
        } else {
            return filePath.substr(0, lastSlash);
        }
    }

} // namespace Common
