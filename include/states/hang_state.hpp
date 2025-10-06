#include "state.hpp"

class HangState : public State
{
    private:
        bool keyPressed;
    public:
        HangState();
        void callback() override;
};
