#include "odvcontrol.h"

#include <cstdlib>
#include <iostream>
#include <sys/wait.h>
#include <stdio.h>

namespace SimulationGame {

    OdvControl::OdvControl(const std::string& cid, const std::string& freq, const std::string& configurationFile)
        : cid(cid), freq(freq), configurationFile(configurationFile) {
    }

    OdvControl::~OdvControl() {
    }

    void OdvControl::start() {
        startProcess(std::string("odsupercomponent --cid=" + cid + " --configuration=" + configurationFile).c_str());
        startProcess(std::string("odsimvehicle --cid=" + cid + " --freq=" + freq).c_str());
        startProcess(std::string("odsimirus --cid=" + cid + " --freq=" + freq).c_str());
        startProcess(std::string("odcockpit --cid=" + cid).c_str());
        startProcess(std::string("odsimcamera --cid=" + cid + " --freq=" + freq).c_str());
        sleep(5);
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
        std::cout << "Shutting down process " << pid << std::endl;
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
