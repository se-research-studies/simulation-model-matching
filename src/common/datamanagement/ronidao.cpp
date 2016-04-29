#include "ronidao.h"

#include <cstring>
#include <fstream>

namespace Common {

  RoniDAO::RoniDAO() {
  }

  RoniDAO::~RoniDAO() {
  }

  std::vector<Region> RoniDAO::load(const std::string recordingFilename) const {
    std::vector<Region> result;
    Json::Value root = readFile(toRoniFilename(recordingFilename));
    Json::Value regionArray = root["regions"];
    for (auto iterator = regionArray.begin(); iterator != regionArray.end(); ++iterator) {
      result.push_back(toRegion(*iterator));
    }

    return result;
  }

  std::string RoniDAO::toRoniFilename(const std::string& recordingFilename) const {
    std::string strippedRecordingName = recordingFilename.substr(0, recordingFilename.find_last_of("."));
    return strippedRecordingName + ".roni";
  }

  Json::Value RoniDAO::readFile(const std::string& roniFilename) const {
    std::ifstream file;
    file.open(roniFilename);
    if (!file.is_open()) {
      throw std::runtime_error("Could not open " + roniFilename + ": " + std::strerror(errno));
    }
    Json::Value root;
    file >> root;
    return root;
  }

  Region RoniDAO::toRegion(const Json::Value& value) const {
    return Region(toCoordinates(value["topLeft"]),
        toCoordinates(value["topRight"]),
        toCoordinates(value["bottomLeft"]),
        toCoordinates(value["bottomRight"]));
  }

  Coordinates RoniDAO::toCoordinates(const Json::Value& value) const {
    uint32_t x = value["x"].asUInt();
    uint32_t y = value["y"].asUInt();
    return Coordinates(x, y);
  }

} // namespace FeatureExtraction
