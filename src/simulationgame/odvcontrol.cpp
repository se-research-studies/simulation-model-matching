#include "odvcontrol.h"

#include <cstdlib>
#include <iostream>
#include <sys/wait.h>
#include <stdio.h>

namespace SimulationGame {

    OdvControl::OdvControl() {
    }

    OdvControl::~OdvControl() {
    }

    void OdvControl::start() {
        startProcess("odsupercomponent --cid=111");
        startProcess("odsimvehicle --cid=111 --freq=10");
        startProcess("odsimirus --cid=111 --freq=10");
        startProcess("odcockpit --cid=111");
        startProcess("odsimcamera --cid=111 --freq=10");
    }

    void OdvControl::stop() {
        while (!runningProcesses.empty()) {
            stopProcess(runningProcesses.front());
            runningProcesses.pop();
        }
    }

    void OdvControl::startProcess(const char* command) {
        pid_t pid = vfork();
        if (pid == 0) {
            if (execlp("xterm", "xterm", "-e", command, (char*)0) == -1) {
                perror("execlp");
            }
            exit(EXIT_SUCCESS);
        } else {
            runningProcesses.push(pid);
            std::cout << "Running " << command << " with PID " << pid << std::endl;
        }
    }

    void OdvControl::stopProcess(pid_t pid) {
        kill(pid, SIGTERM);
    }

} // namespace SimulationGame
