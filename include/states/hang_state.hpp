#include "state.hpp"

class HangState : public State
{
    public:
        HangState();
        void callback() override;
};
