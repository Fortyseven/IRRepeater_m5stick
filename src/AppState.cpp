#include <stdlib.h>
#include "AppState.h"

/* -------------------------------- */
void AppState::registerState(IState *state, int state_id)
{
    if (state_id >= 0 && state_id < MAX_STATE)
    {
        this->states[state_id] = state;
    }
}

/* -------------------------------- */
void AppState::loop()
{
    this->states[current_state]->loop(this);
}

/* -------------------------------- */
void AppState::changeState(int new_state)
{
    if (current_state >= 0)
    {
        states[current_state]->onExit(this, states[new_state]);
        states[new_state]->onEnter(this, states[current_state]);
    }
    else
    {
        states[new_state]->onEnter(this, NULL);
    }

    current_state = new_state;
}
