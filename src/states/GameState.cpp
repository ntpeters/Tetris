#include "GameState.h"
#include "../blocks/Tetromino_Type.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

GameState::GameState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn ) : BaseState( displayIn, event_queueIn, statesIn ) {
    totalTime = 0.0;
    piece = new Tetromino( Tetromino_Type::I_BLOCK );
    writeLog( LOG_DEBUG, "New game state created" );
}

GameState::~GameState() {
    writeLog( LOG_DEBUG, "Game state destroyed" );
}

bool GameState::update( double delta ) {
    totalTime += delta;

    piece->update( delta );

    return true;
}

bool GameState::render() { 

    // Clear screen to black
    al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

    double xPix = 300 / 10;
    double yPix = 600 / 20;

    // Draw the X gridlines
    for( int i = 250; i <= 551; i+=xPix) {
        al_draw_line( i, 0, i, 800, al_map_rgb( 255, 255, 255 ), 1);
    }

    // Draw the Y gridlines
    for( int i = 0; i <= 600; i+=yPix) {
        al_draw_line(250, i, 550, i, al_map_rgb( 255, 255, 255 ), 1);
    }

    piece->draw();
    
   return true;
}