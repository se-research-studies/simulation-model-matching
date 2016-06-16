#pragma once

namespace SimulationGame {

    struct Settings;

    class GameRunner {
    public:
        GameRunner();
        virtual ~GameRunner();

    public:
        void start(const Settings& settings);
    };

} // namespace SimulationGame

