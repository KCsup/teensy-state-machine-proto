#include <iostream>
#include "state.hpp"
#include "states/idle_state.hpp"
#include "states/hang_state.hpp"
#include <functional>


int main()
{
    StateMap* stateMap = new StateMap();
    std::cout << "TEST" << std::endl;

    IdleState* idleState = new IdleState();
    stateMap->appendState(idleState);
    HangState* hangState = new HangState();
    stateMap->appendState(hangState);
    // TODO: switch the assigning of next states to be indices
    stateMap->setTransitionCheckResult(idleState, 0, hangState);

    State* currentState = idleState;
    // main execution
    while(true)
    {
        // if the end of traversal has been reached
        if(currentState == NULL)
            break;
        
        currentState->callback();
        for(TransitionFunction* transitionFunc : currentState->getTransitionFuncs())
        {
            if(transitionFunc->transitionCheckFunction())
            {
                currentState = transitionFunc->resultState;
                break;
            }
        }
    }

    delete stateMap;
    return 0;
}
