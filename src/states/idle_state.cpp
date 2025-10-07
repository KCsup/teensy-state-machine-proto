#include "states/idle_state.hpp"
#include <iostream>
#include <chrono>

long timeSec()
{
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


void IdleState::callback()
{
    std::cout << "Idle callback. Running for " << (timeSec() - this->startTime) << " seconds." << std::endl;
}

IdleState::IdleState() : State(), startTime(timeSec())
{
    std::function<bool(void)> tenSecondCheck = [this]() -> bool {
        return (timeSec() - this->startTime) >= 10;
    };

    this->appendTransitionCheck(new TransitionFunction(tenSecondCheck));
}

