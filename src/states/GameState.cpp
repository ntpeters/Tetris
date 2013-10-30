#include "GameState.h"

GameState::GameState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn ) : BaseState( displayIn, event_queueIn, statesIn ) {
    totalTime = 0.0;

    writeLog( LOG_DEBUG, "New game state created" );
}

GameState::~GameState() {
    writeLog( LOG_DEBUG, "Game state destroyed" );
}

bool GameState::update( double delta ) {
    totalTime += delta;

    writeLog( LOG_VERBOSE, "Game Time: %.2f", totalTime );

    if( totalTime >= 25 ) {
        return false;
    }

    return true;
}

bool GameState::render() { 
 
    // Clear screen to black
    al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

   return true;
}