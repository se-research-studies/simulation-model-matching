#pragma once

#include <cstdint>
#include <string>

namespace Common {

    class Measurements {
    public:
        Measurements(const std::string& simulationName, const std::string& recordingName);

    public:        
        std::string getSimulationName() const;

        std::string getRecordingName() const;

        uint32_t getSteps() const;
        void setSteps(uint32_t value);
        void addStep();

        uint32_t getComputationTime() const;
        void setComputationTime(uint32_t value);
        void addToComputationTime(uint32_t value);

        uint32_t getLapTime() const;
        void setLapTime(uint32_t value);

        uint32_t getSteeringActions() const;
        void setSteeringActions(uint32_t value);
        void addSteeringAction();

        uint32_t getMemory() const;
        void setMemory(uint32_t value);

    private:
        const std::string simulationName;
        const std::string recordingName;
        uint32_t steps = 0;
        uint32_t computationTime = 0;
        uint32_t lapTime = 0;
        uint32_t steeringActions = 0;
        uint32_t memory = 0;
    };

} // namespace Common

