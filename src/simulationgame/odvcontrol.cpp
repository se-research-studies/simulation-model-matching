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
        if (pid == 0) { // We are the child process
            if (execlp("xterm", "xterm", "-e", command, static_cast<char*>(nullptr)) == -1) {
                perror("execlp");
            }
            exit(EXIT_SUCCESS);
        } else { // We are the parent process
            runningProcesses.push(pid);
            std::cout << "Running " << command << " with PID " << pid << std::endl;
        }
    }

    void OdvControl::stopProcess(pid_t pid) {
        kill(pid, SIGTERM);
        if (!waitForProcessToStop(pid, 5)) {
            kill(pid, SIGKILL);
        }
    }

    bool OdvControl::waitForProcessToStop(pid_t pid, uint8_t seconds) {
        for (int i = 0; i < seconds; i++) {
            sleep(1);
            if (waitpid(pid, nullptr, WNOHANG) == pid) {
                return true;
            }
        }
        return false;
    }

} // namespace SimulationGame
