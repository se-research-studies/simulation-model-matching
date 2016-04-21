#include "correlationdao.h"

#include <cstring>
#include <fstream>
#include <type_traits>

namespace FeatureExtraction {

  CorrelationDAO::CorrelationDAO()
  {
  }

  CorrelationDAO::~CorrelationDAO()
  {
  }

  std::unordered_map<std::string, Correlation> CorrelationDAO::load(const std::string& simulationFilename)
  {
    std::unordered_map<std::string, Correlation> result;

    Json::Value root = readFile(toCorFilename(simulationFilename));
    Json::Value correlationArray = root["correlations"];
    for (auto iterator = correlationArray.begin(); iterator != correlationArray.end(); ++iterator) {
      std::string recordingFile = (*iterator)["recordingFile"].asString();
      uint32_t startFrame = (*iterator)["startFrame"].asUInt();
      uint32_t endFrame = (*iterator)["endFrame"].asUInt();
      Json::Value startPosition = (*iterator)["startPosition"];
      uint32_t startX = startPosition["x"].asUInt();
      uint32_t startY = startPosition["y"].asUInt();
      uint16_t startTheta = startPosition["theta"].asUInt();
      Json::Value endPosition = (*iterator)["endPosition"];
      uint32_t endX = endPosition["x"].asUInt();
      uint32_t endY = endPosition["y"].asUInt();
      uint16_t endTheta = endPosition["theta"].asUInt();

      Position startPos({ startX, startY }, startTheta);
      Position endPos({ endX, endY }, endTheta);
      Correlation correlation(startFrame, endFrame, startPos, endPos);
      result.insert({recordingFile, correlation});
    }

    return result;
  }

  std::string CorrelationDAO::toCorFilename(const std::string& simulationFilename) const
  {
    std::string strippedSimulationName = simulationFilename.substr(0, simulationFilename.find_last_of("."));
    return strippedSimulationName + ".cor";
  }

  Json::Value CorrelationDAO::readFile(const std::string& corFilename) const
  {
    std::ifstream file;
    file.open(corFilename);
    if (!file.is_open()) {
      throw std::runtime_error("Could not open " + corFilename + ": " + std::strerror(errno));
    }
    Json::Value root;
    file >> root;
    return root;
  }

} // namespace FeatureExtraction
