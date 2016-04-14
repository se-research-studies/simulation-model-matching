#pragma once

#include <NoiseSimulation/DataSource>

namespace NoiseSimulation {

    class FileDataSource : public DataSource
    {
    public:
        virtual ~FileDataSource();

    public:
        FileDataSource(const FileDataSource&) = delete;
        FileDataSource& operator=(const FileDataSource&) = delete;

    private:
        FileDataSource();

    public:
        static void createInstance();
    };

} // namespace NoiseSimulation

