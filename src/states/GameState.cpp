#include "GameState.h"
#include "BaseState.h"
#include "../util/simplog.h"
#include <stdio.h>
#include <allegro5/allegro.h>

GameState::GameState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn ) : BaseState( displayIn, event_queueIn ) {
	writeLog( LOG_DEBUG, "New game state created" );
}

GameState::~GameState() {
	writeLog( LOG_DEBUG, "Game state destroyed" );
}

bool GameState::update( double delta ) {
	
	return true;
}

bool GameState::render() { 
 
   return true;
}