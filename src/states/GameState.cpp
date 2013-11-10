#include "GameState.h"
#include "../blocks/Tetromino_Type.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

GameState::GameState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn ) : BaseState( displayIn, event_queueIn, statesIn ) {
    totalTime = 0.0;
    updateCounter = 0;
    currentPiece = this->getRandomPiece();
    nextPiece = this->getRandomPiece();
    nextPiece->setX( 580 );
    nextPiece->setY( 60 );
    writeLog( LOG_DEBUG, "New game state created" );
}

GameState::~GameState() {
    writeLog( LOG_DEBUG, "Game state destroyed" );
}

bool GameState::update( double delta ) {
    totalTime += delta;
    updateCounter++;


    ALLEGRO_EVENT ev;
    ALLEGRO_TIMEOUT timeout;
    al_init_timeout( &timeout, 0.01 );
 
    bool got_event = al_wait_for_event_until( event_queue, &ev, &timeout );
 
    if( got_event ) {
        if( ev.type == ALLEGRO_EVENT_KEY_DOWN ) {
            if( ev.keyboard.keycode == ALLEGRO_KEY_LEFT ) {
                currentPiece->moveLeft( delta );
            } else if( ev.keyboard.keycode == ALLEGRO_KEY_RIGHT ) {
                currentPiece->moveRight( delta );
            }
            
            if( ev.keyboard.keycode == ALLEGRO_KEY_SPACE ) {
                currentPiece->moveDown( delta );
            }
        }
    }
    writeLog( LOG_VERBOSE, "%.2f", totalTime );
    if( totalTime >= 20  && currentPiece != nullptr ) {
        // writeLog( LOG_VERBOSE, "piece processing" );
        currentPiece->update( delta );

        if( checkCollision( currentPiece ) ) {
           delete currentPiece;
           currentPiece = nextPiece;
           nextPiece = this->getRandomPiece();
           nextPiece->setX( 580 );
           nextPiece->setY( 60 );
           currentPiece->setX( 280 );
           currentPiece->setY( -29 );
           // writeLog( LOG_VERBOSE, "deleted" );
        }
        totalTime = 0;
    }

    return true;
}

bool GameState::checkCollision( Tetromino* tet ) {
    Block** check = tet->getBlocks();
    int x = tet->getX();
    int y = tet->getY();
    int xA = (tet->getX()-250)/30;
    int yA = tet->getY()/30;
    // writeLog( LOG_VERBOSE, "[%d, %d]", xA, yA );
    for( int i = 0; i < tet->getArrayWidth(); i++ ) {
        // writeLog( LOG_VERBOSE, "loop 1" );
        for( int j = tet->getArrayHeight()-1; j >= 0; j-- ) {
            // writeLog( LOG_VERBOSE, "loop 2" );
            // writeLog( LOG_VERBOSE, "check[%d, %d] - grid[%d, %d]", i, j, xA+i, yA+j );
            if( ( check[i][j].doesExist() &&  grid[xA+i][yA+1+j].doesExist() ) ){
                // writeLog( LOG_VERBOSE, "if" );
                for( int k = 0; k < tet->getArrayWidth(); k++ ) {
                    // writeLog( LOG_VERBOSE, "loop 3" );
                    for( int l = 0; l < tet->getArrayHeight(); l++ ) {
                        // writeLog( LOG_VERBOSE, "loop 4" );
                        if( check[l][k].doesExist() ) {
                            grid[xA+l][yA+k] = check[l][k];
                        }
                    }
                }
                //writeLog( LOG_VERBOSE, "done" );
                //al_rest(1000);
                return true;
            }
        }
    }

    return false;
}

Tetromino* GameState::getRandomPiece() {
    srand( time( NULL ) );
    int rNum = rand() % 6;

    switch( rNum ) {
        case 0:
            return new Tetromino( Tetromino_Type::I_BLOCK );
        case 1:
            return new Tetromino( Tetromino_Type::O_BLOCK );
        case 2:
            return new Tetromino( Tetromino_Type::L_BLOCK );
        case 3:
            return new Tetromino( Tetromino_Type::J_BLOCK );
        case 4:
            return new Tetromino( Tetromino_Type::T_BLOCK );
        case 5:
            return new Tetromino( Tetromino_Type::S_BLOCK );
        case 6:
            return new Tetromino( Tetromino_Type::Z_BLOCK );
    }
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

    // Draw the grid
    for( int i = 0; i < 10; i++ ) {
        for( int j = 0; j < 20; j++ ) {
            if( grid[i][j].doesExist() ) {
                if( j != 19 ) {
                    al_draw_tinted_bitmap( grid[i][j].getBlock(), grid[i][j].getColor(), 250 + i * 30, 1 + j * 30, 0 );
                    /*Block** check = currentPiece->getBlocks();
                    int xA = (currentPiece->getX()-250)/30;
                    int yA = currentPiece->getY()/30;
                    if( check[l][k].doesExist() ) {
                        grid[xA+l][yA+k] = check[l][k];
                    }*/
                } else {
                    al_draw_tinted_bitmap( grid[i][j].getBlock(), al_map_rgb(150,180,200), 250 + i * 30, 1 + j * 30, 0 );
                }
            } else if( j == 19 ) {
                grid[i][j].toggleExists();
            }
        }
    }

    // Do not draw piece if it currently does not exists
    if( currentPiece != nullptr ) {
        //writeLog( LOG_VERBOSE, "drawing" );
        currentPiece->draw();    
    }

    if( nextPiece != nullptr ) {
        nextPiece->draw();
    }
    
   return true;
}