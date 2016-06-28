#include "correlationdao.h"

#include <cstring>
#include <fstream>

namespace Common {

    CorrelationDAO::CorrelationDAO() {
    }

    CorrelationDAO::~CorrelationDAO() {
    }

    std::vector<Correlation> CorrelationDAO::load(const std::string& correlationFilename) const
    {
        std::vector<Correlation> result;
        Json::Value root = readFile(correlationFilename);
        Json::Value correlationArray = root["correlations"];
        for (auto iterator = correlationArray.begin(); iterator != correlationArray.end(); ++iterator) {
            result.push_back(toCorrelation(*iterator));
        }
        return result;
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
        Correlation result(toRectangle(value));
        Json::Value sectionArray = value["sections"];
        for (auto iterator = sectionArray.begin(); iterator != sectionArray.end(); ++iterator) {
            result.addSection(toRecordingSection(*iterator));
        }
        return result;
    }

    Rectangle CorrelationDAO::toRectangle(const Json::Value& value) const
    {
        Coordinates topLeft = toCoordinates(value["topLeft"]);
        Coordinates bottomRight = toCoordinates(value["bottomRight"]);
        return Rectangle(topLeft, bottomRight);
    }

    Coordinates CorrelationDAO::toCoordinates(const Json::Value& value) const {
        int x = value["x"].asInt();
        int y = value["y"].asInt();
        return Coordinates(x, y);
    }

    RecordingSection CorrelationDAO::toRecordingSection(const Json::Value& value) const
    {
        std::string recordingName = value["recordingName"].asString();
        uint32_t startFrame = value["startFrame"].asUInt();
        uint32_t endFrame = value["endFrame"].asUInt();
        return RecordingSection(recordingName, startFrame, endFrame);
    }

} // namespace FeatureExtraction
