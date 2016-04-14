#pragma once

#include <NoiseSimulation/DataSource>

namespace NoiseSimulation {

    class Noise;
    class FrameCorrelation;
    class Area;

    class SQLiteDataSource : public DataSource
    {
    public:
        virtual ~SQLiteDataSource();

    public:
        SQLiteDataSource(const SQLiteDataSource&) = delete;
        SQLiteDataSource& operator=(const SQLiteDataSource&) = delete;

    private:
        SQLiteDataSource();

    public:
        static void createInstance() {
            instance = new SQLiteDataSource();
        }

    public:
        void saveNoise(const Noise& noise) override;

    };

} // namespace NoiseSimulation

