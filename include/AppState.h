#pragma once

#include "IState.h"

#define MAX_STATE 10

class AppState
{
    IState *states[MAX_STATE];
    int current_state = -1;

public:
    void registerState(IState *state, int state_id);
    void loop();
    void changeState(int new_state);
};
