#include "BaseState.h"
#include "../util/SimpleLogger/simplog.h"
#include <iostream>

BaseState::BaseState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn ) {
    display     = displayIn;
    event_queue = event_queueIn;
    states      = statesIn;

    writeLog( LOG_VERBOSE, "New state created (base state constructor)" );
}

BaseState::~BaseState() {
    writeLog( LOG_VERBOSE, "State destroyed (base state destructor)" );
}
