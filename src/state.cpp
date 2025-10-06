#include "state.hpp"

TransitionFunction::TransitionFunction(std::function<bool(void)> transitionFunc) :
    transitionCheckFunction(transitionFunc), resultState(NULL)
{}

void TransitionFunction::setResultState(State* newResultState)
{
    this->resultState = newResultState;
}

State::State() : transitionCheckFuncs(new std::vector<TransitionFunction*>)
{}

State::~State()
{
    for(TransitionFunction* tfP : *this->transitionCheckFuncs)
        delete tfP;

    delete this->transitionCheckFuncs;
}

void State::appendTransitionCheck(TransitionFunction* transitionFunc)
{
    this->transitionCheckFuncs->push_back(transitionFunc);
}

const std::vector<TransitionFunction*> State::getTransitionFuncs()
{
    return *this->transitionCheckFuncs;
}

void StateMap::appendState(State* state)
{
    std::vector<TransitionFunction*>* stateTransitions =
        new std::vector<TransitionFunction*>;

    for(TransitionFunction* transitionFunc : state->getTransitionFuncs())
        // sets the result state to NULL, by default (to ensure all states
        // can be instantiated before linking)
        stateTransitions->push_back(transitionFunc);

    this->stateMap->insert({ state, stateTransitions });
}

void StateMap::setTransitionCheckResult(State* state,
                                        int checkFuncIndex,
                                        State* resultState)
{
    this->stateMap->at(state)->at(checkFuncIndex)->setResultState(resultState);
}

StateMap::StateMap()
    : stateMap(new std::unordered_map<State*,
                                      std::vector<TransitionFunction*>*>)
{}

StateMap::~StateMap()
{
    for(std::pair<State*, std::vector<TransitionFunction*>*> mapPair : *this->stateMap)
    {
        delete mapPair.first;
        delete mapPair.second;
    }
}
