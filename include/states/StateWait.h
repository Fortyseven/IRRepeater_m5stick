#pragma once
#include "IState.h"

class StateWait : public IState
{
public:
    void onEnter(AppState *app_state, IState *from_state);
    void loop(AppState *app_state);
};