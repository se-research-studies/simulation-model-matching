#pragma once

#include <memory>
#include <unordered_map>

#include <Data/Correlation>

namespace FeatureExtraction {

  class CorrelationDAO
  {
  public:
    CorrelationDAO();
    virtual ~CorrelationDAO();

  public:
    std::unordered_map<std::string, Correlation> load(const std::string& simulationFilename);
  };

} // namespace FeatureExtraction

