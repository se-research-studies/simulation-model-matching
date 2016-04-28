#include "correlationdao.h"

#include <cstring>
#include <fstream>

namespace Common {

  CorrelationDAO::CorrelationDAO() {
  }

  CorrelationDAO::~CorrelationDAO() {
  }

  std::unordered_map<std::string, Correlation> CorrelationDAO::load(const std::string& simulationFilename) const {
    std::unordered_map<std::string, Correlation> result;

    Json::Value root = readFile(toCorFilename(simulationFilename));
    Json::Value correlationArray = root["correlations"];
    for (auto iterator = correlationArray.begin(); iterator != correlationArray.end(); ++iterator) {
      std::string recordingFile = (*iterator)["recordingFile"].asString();
      result.insert({recordingFile, toCorrelation(*iterator)});
    }

    return result;
  }

  std::string CorrelationDAO::toCorFilename(const std::string& simulationFilename) const {
    std::string strippedSimulationName = simulationFilename.substr(0, simulationFilename.find_last_of("."));
    return strippedSimulationName + ".cor";
  }

  Json::Value CorrelationDAO::readFile(const std::string& corFilename) const {
    std::ifstream file;
    file.open(corFilename);
    if (!file.is_open()) {
      throw std::runtime_error("Could not open " + corFilename + ": " + std::strerror(errno));
    }
    Json::Value root;
    file >> root;
    return root;
  }

  Correlation CorrelationDAO::toCorrelation(const Json::Value& value) const {
    uint32_t startFrame = value["startFrame"].asUInt();
    uint32_t endFrame = value["endFrame"].asUInt();
    return Correlation(startFrame, endFrame, toPosition(value["startPosition"]), toPosition(value["endPosition"]));
  }

  Position CorrelationDAO::toPosition(const Json::Value& value) const {
    uint32_t x = value["x"].asUInt();
    uint32_t y = value["y"].asUInt();
    uint16_t theta = value["theta"].asUInt();
    return Position(x, y, theta);
  }

} // namespace FeatureExtraction
