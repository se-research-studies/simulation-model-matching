#include "utils.h"

namespace Common {

    std::string Utils::removeBraces(std::string from) {
        from.erase(0, 1);
        from.pop_back();
        return from;
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
