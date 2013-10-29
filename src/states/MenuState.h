#pragma once
#include "BaseState.h"
#include <allegro5/allegro.h>

class MenuState : public BaseState {
public:
    MenuState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn );
    ~MenuState();
    bool update( double delta );
    bool render();
};