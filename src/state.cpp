#include "state.hpp"

void State::appendTransitionCheck(bool (*transitionFunc)())
{
    this->transitionCheckFuncs.push_back(transitionFunc);
}

const std::vector<bool (*)()> State::getTransitionFuncs()
{
    return this->transitionCheckFuncs;
}

void StateMap::appendState(State* state)
{
    std::vector<TransitionLink>* stateTransitions =
        new std::vector<TransitionLink>;

    for(bool (*transitionFunc)() : state->getTransitionFuncs())
        // sets the result state to NULL, by default (to ensure all states
        // can be instantiated before linking)
        stateTransitions->push_back({ transitionFunc, NULL });

    this->stateMap->insert({ state, stateTransitions });
}

void StateMap::setTransitionCheckResult(State* state,
                                        int checkFuncIndex,
                                        State* resultState)
{
    this->stateMap->at(state)->at(checkFuncIndex).resultState = resultState;
}
