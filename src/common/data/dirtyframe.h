#pragma once

#include <memory>
#include <vector>

#include <FeatureSimulation/Common/Data/feature.h>

namespace Common {

class DirtyFrame {
public:
    DirtyFrame(std::vector<Feature>&& features);
    DirtyFrame() = default;
    DirtyFrame(DirtyFrame&& other) = default;

public:
    DirtyFrame(const DirtyFrame&) = delete;
    DirtyFrame& operator=(const DirtyFrame&) = delete;

public:
    const std::vector<Feature>& getFeatures() const;
    uint32_t getFeatureCount() const;
    void addFeature(Feature&& feature);

    std::string toSqlString() const;
    static DirtyFrame fromSqlString(const std::string& stringFormatted);

private:
    std::vector<Feature> features;
};

} // namespace FeatureExtraction

