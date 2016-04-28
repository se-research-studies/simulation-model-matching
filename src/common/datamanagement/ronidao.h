#pragma once

#include <vector>

#include <jsoncpp/json/json.h>

#include <FeatureSimulation/Common/Data/Region>

namespace Common {

  class RoniDAO
  {
  public:
    RoniDAO();
    virtual ~RoniDAO();

  public:
    std::vector<Region> load(const std::string recordingFilename) const;

  private:
    std::string toRoniFilename(const std::string& recordingFilename) const;
    Json::Value readFile(const std::string& roniFilename) const;
    Region toRegion(const Json::Value& value) const;
    Coordinates toCoordinates(const Json::Value& value) const;
  };

} // namespace FeatureExtraction

