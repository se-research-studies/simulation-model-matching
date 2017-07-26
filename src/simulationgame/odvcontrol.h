#pragma once

#include <queue>
#include <stdint.h>
#include <string>
#include <unistd.h>

namespace SimulationGame {

    class OdvControl {
    public:
        OdvControl();
        virtual ~OdvControl();

    public:
        void start(const std::string& cid, const std::string& freq, const std::string& configurationFile);
        void stop();

    private:
        void startProcess(const char* command);
        void stopProcess(pid_t pid);
        bool waitForProcessToStop(pid_t pid, uint8_t seconds);

    private:
        std::queue<pid_t> runningProcesses;
    };

} // namespace SimulationGame

