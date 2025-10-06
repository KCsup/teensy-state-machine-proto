#include "state.hpp"

class IdleState : public State
{
    public:
        IdleState();
        long startTime;
        void callback() override;
};

