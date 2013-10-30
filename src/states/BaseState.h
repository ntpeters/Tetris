#pragma once
#include <stack>
#include "../util/simplog.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class BaseState {
public:
    BaseState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn );
    virtual ~BaseState();
    virtual bool update( double delta ) = 0;
    virtual bool render() = 0;

protected:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* event_queue;
    std::stack<BaseState*>* states;
};