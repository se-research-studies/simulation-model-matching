#pragma once

#include <memory>
#include <unordered_map>

#include <jsoncpp/json/json.h>

//#include <FeatureSimulation/Common/Data/correlation.h>

namespace Common {

class CorrelationDAO
{
public:
    CorrelationDAO();
    virtual ~CorrelationDAO();

//public:
//    std::unordered_map<std::string, Correlation> load(const std::string& simulationFilename) const;

//private:
//    std::string toCorFilename(const std::string& simulationFilename) const;
//    Json::Value readFile(const std::string& corFilename) const;
//    Correlation toCorrelation(const Json::Value& value) const;
//    Position toPosition(const Json::Value& value) const;
};

} // namespace FeatureExtraction

