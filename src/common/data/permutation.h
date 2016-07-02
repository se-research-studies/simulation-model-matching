#pragma once

#include <unordered_map>

#include <FeatureSimulation/Common/Data/featureset.h>
#include <FeatureSimulation/Common/Data/rectangle.h>
#include <FeatureSimulation/Common/Data/recordingsection.h>

namespace Common {

    typedef std::unordered_map<Common::Rectangle, std::unique_ptr<Common::FeatureSet>> LocalFeatureSets;

    struct Permutation {
        Permutation() = default;
        Permutation(const Permutation&) = delete;
        Permutation(Permutation&& other) = default;

        std::string index;
        LocalFeatureSets localFeatureSets;

        Permutation& operator=(const Permutation&) = delete;
        Permutation& operator=(Permutation&& other) = default;
    };

} // namespace Common

