#pragma once

// #include "AppState.h"

class AppState;

class IState
{
public:
    virtual void onEnter(AppState *app_state, IState *from_state){};
    virtual void onExit(AppState *app_state, IState *to_state){};

    virtual void loop(AppState *app_state);
};