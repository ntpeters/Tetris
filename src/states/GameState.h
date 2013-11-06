#pragma once
#include "BaseState.h"
#include <allegro5/allegro.h>

class GameState : public BaseState {
public:
    GameState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn );
    ~GameState();
    bool update( double delta );
    bool render();

    ALLEGRO_BITMAP* pic;
    ALLEGRO_FONT* font18;

private:
    double totalTime;
};