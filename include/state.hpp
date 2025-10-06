#pragma once

#include <vector>
#include <unordered_map>
#include <functional>

// prototype for TransitionFunction usage
class State;

class TransitionFunction
{
    public:
        // constructor
        // set result state to NULL by default
        TransitionFunction(std::function<bool(void)> transitionFunc);
        std::function<bool(void)> transitionCheckFunction;
        State* resultState;
        void setResultState(State* resultState);
};

class State
{
    private:
        // vector of boolean function pointers
        std::vector<TransitionFunction*>* transitionCheckFuncs;
    public:
        virtual void callback() = 0;
        // to be called in the constructors of each state definition
        void appendTransitionCheck(TransitionFunction* transitionFunc);
        const std::vector<TransitionFunction*> getTransitionFuncs();
        // constructor for instantiating
        State();
        // allows for all sub-destructors to be called
        virtual ~State();
};

class StateMap
{
    // access the transistion check functions for each given state
    // then, that function is connected to the state that will be
    // transitioned to IF the transition function returns true
    private:
        std::unordered_map<State*,
                           std::vector<TransitionFunction*>*>* stateMap;
    public:
        // will append all the transition check functions,
        // but will set the result state to "NULL"
        void appendState(State* state);

        // will set the resulting state for the true case
        // of the specific check function
        // returns if the append was successful
        // TODO: consider having boolean return for successful set?
        void setTransitionCheckResult(State* state,
                                      int checkFuncIndex,
                                      State* resultState);
        // constructor
        // instantiates the stateMap map
        StateMap();
        // destructor
        // should delete all states and the list of transition funcs
        ~StateMap();
};

