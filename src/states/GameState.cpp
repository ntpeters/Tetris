#include "GameState.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

GameState::GameState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn ) : BaseState( displayIn, event_queueIn, statesIn ) {
    totalTime = 0.0;

    const char* bmpFile = "/home/nate/git/Tetris/res/img/block.png";
/*    ALLEGRO_FILE * tstFile = al_fopen(bmpFile, "r");
    if( !tstFile ) {
        writeLog( LOG_FATAL, "Failed to load bmp as file" );
        throw -1;
    } else {
        writeLog( LOG_VERBOSE, "Loaded bmp as file successfully" );
    }*/
    pic = al_load_bitmap( bmpFile );
    if( !pic ) {
        writeLog( LOG_ERROR, "Failed to load bitmap!" );
        throw -1;
    } else {
        writeLog( LOG_VERBOSE, "Bitmap loaded successfully" );
    }

    writeLog( LOG_DEBUG, "New game state created" );
}

GameState::~GameState() {
    writeLog( LOG_DEBUG, "Game state destroyed" );
}

bool GameState::update( double delta ) {
    totalTime += delta;

    //writeLog( LOG_VERBOSE, "Game Time: %.2f", totalTime );

/*    if( totalTime >= 25 ) {
        return false;
    }*/

    return true;
}

bool GameState::render() { 

    // Clear screen to black
    al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

    double xPix = 300 / 10;
    double yPix = 600 / 20;


    for( int i = 250; i <= 550; i+=xPix) {
        al_draw_line( i, 0, i, 800, al_map_rgb( 255, 255, 255 ), 1);
    }

    for( int i = 0; i < 600; i+=yPix) {
        al_draw_line(250, i, 550, i, al_map_rgb( 255, 255, 255 ), 1);
    }

    al_draw_bitmap(pic, 200, 200, 0);
 
   return true;
}