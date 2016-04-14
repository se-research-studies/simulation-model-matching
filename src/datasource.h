#pragma once

#include <stdexcept>

namespace NoiseSimulation {

    class Noise;
    class FrameCorrelation;
    class Area;

    class DataSource
    {
    public:
        static DataSource& getInstance() {
            if (instance != nullptr) {
                return *instance;
            } else {
                throw std::runtime_error("createInstance() of one of the subclasses must be called before using DataSource");
            }
        }

    protected:
        DataSource();

    public:
        DataSource(const DataSource&) = delete;
        DataSource& operator=(const DataSource&) = delete;

    protected:
        virtual void saveNoise(const Noise& noise) = 0;

    protected:
        static DataSource* instance;
    };

} // namespace NoiseSimulation

