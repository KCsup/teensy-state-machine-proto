#include "states/hang_state.hpp"
#include <iostream>

void HangState::callback()
{
    std::cout << "Hanging state." << std::endl;
}

HangState::HangState() : State(), keyPressed(false)
{
    // will loop infinitely
    this->appendTransitionCheck(new TransitionFunction([this]() -> bool {
                                                       return this->keyPressed;
                                                   }));
}
