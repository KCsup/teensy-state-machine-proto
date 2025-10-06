#include <vector>
#include <unordered_map>

class State {
    private:
        // vector of boolean function pointers
        std::vector<bool (*)()> transitionCheckFuncs;
    public:
        virtual void callback() = 0;
        // to be called in the constructors of each state definition
        void appendTransitionCheck(bool (*transitionFunc)());
        const std::vector<bool (*)()> getTransitionFuncs();
        
};

typedef struct {
    bool (*transitionCheckFunc)();
    State* resultState;
} TransitionLink;

class StateMap {
    // access the transistion check functions for each given state
    // then, that function is connected to the state that will be
    // transitioned to IF the transition function returns true
    private:
        std::unordered_map<State*,
                           std::vector<TransitionLink>*>* stateMap;
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
        // destructor
        // should delete all states and the list of transition funcs
        ~StateMap();
};
