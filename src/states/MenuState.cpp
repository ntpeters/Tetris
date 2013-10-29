#include "MenuState.h"
#include "BaseState.h"
#include "../util/simplog.h"
#include <stdio.h>
#include <allegro5/allegro.h>

MenuState::MenuState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn ) : BaseState( displayIn, event_queueIn ) {
	writeLog( LOG_DEBUG, "New menu state created" );
}

MenuState::~MenuState() {
	writeLog( LOG_DEBUG, "Menu state destroyed" );
}

bool MenuState::update( double delta ) {
	
	return true;
}

bool MenuState::render() { 
 
   return true;
}