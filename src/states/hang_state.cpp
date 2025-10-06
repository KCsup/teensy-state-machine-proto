#include "states/hang_state.hpp"
#include <iostream>

void HangState::callback()
{
    std::cout << "Hanging state." << std::endl;
}

HangState::HangState() : State()
{
    // will loop infinitely
    this->appendTransitionCheck(new TransitionFunction([]() -> bool {
                                                       return false;
                                                   }));
}
