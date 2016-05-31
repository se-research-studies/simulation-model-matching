#pragma once

#include <queue>
#include <unistd.h>

namespace SimulationGame {

    class OdvControl {
    public:
        OdvControl();
        virtual ~OdvControl();

    public:
        void start();
        void stop();

    private:
        void startProcess(const char* command);
        void stopProcess(pid_t pid);

    private:
        std::queue<pid_t> runningProcesses;
    };

} // namespace SimulationGame

