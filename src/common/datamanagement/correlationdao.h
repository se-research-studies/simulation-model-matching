#pragma once

#include <memory>
#include <unordered_map>

#include <jsoncpp/json/json.h>

#include <FeatureSimulation/Common/Data/correlation.h>

namespace Common {

    class CorrelationDAO
    {
    public:
        CorrelationDAO();
        virtual ~CorrelationDAO();

    public:
        std::vector<Correlation> load(const std::string& correlationFilename) const;

    private:
        Json::Value readFile(const std::string& corFilename) const;
        Correlation toCorrelation(const Json::Value& value) const;
        Rectangle toRectangle(const Json::Value& value) const;
        Coordinates toCoordinates(const Json::Value& value) const;
        RecordingSection toRecordingSection(const Json::Value& value) const;
    };

} // namespace FeatureExtraction

