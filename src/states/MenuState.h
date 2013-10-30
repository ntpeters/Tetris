#pragma once
#include "BaseState.h"
#include "GameState.h"
#include <allegro5/allegro.h>

#include <stdio.h>

class MenuState : public BaseState {
public:
    MenuState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn );
    ~MenuState();
    bool update( double delta );
    bool render();

private:
    double totalTime;
    bool gameRan;
    ALLEGRO_FONT* font18;
};