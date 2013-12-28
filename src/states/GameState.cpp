#include "GameState.h"
#include "../entities/Tetromino_Type.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

GameState::GameState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn ) : BaseState( displayIn, event_queueIn, statesIn ) {
    totalTime = 0.0;
    updateCounter = 0;

    const char* bmpFile = "res/img/block2.png";

    blockImg = al_load_bitmap( bmpFile );
    if( !blockImg ) {
        writeLog( LOG_FATAL, "Failed to load bitmap!" );
        throw -1;
    } else {
        writeLog( LOG_VERBOSE, "Bitmap loaded successfully" );
    }

    currentPiece = this->getRandomPiece( blockImg );
    nextPiece = this->getRandomPiece( blockImg );
    nextPiece->setX( 580 );
    nextPiece->setY( 60 );

    grid = new Grid( blockImg );
    writeLog( LOG_DEBUG, "New game state created" );
}

GameState::~GameState() {
    writeLog( LOG_DEBUG, "Game state destroyed" );
}

bool GameState::update( double delta ) {
    //writeLog( LOG_VERBOSE, "update" );

    totalTime += delta;
    


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
            nextPiece = this->getRandomPiece( blockImg);
            nextPiece->setX( 580 );
            nextPiece->setY( 60 );
            currentPiece->setX( 280 );
            currentPiece->setY( -58 );
        }
         totalTime = 0;
         updateCounter++;
    }

    return true;
}

bool GameState::checkCollision( Tetromino* tet ) {
    std::vector<std::vector<Block>> check = tet->getBlocks();
    int xA = (tet->getX()-250)/30;
    int yA = tet->getY()/30;
    //writeLog( LOG_VERBOSE, "[%d, %d]", xA, yA );
    for( int i = 0; i < tet->getArrayWidth(); i++ ) {
        for( int j = tet->getArrayHeight()-1; j >= 0; j-- ) {
            if( ( check[i][j].doesExist() &&  grid->get( yA+1+j, xA+i )->doesExist() ) || yA + 1 >= 19 ){
                for( int k = 0; k < tet->getArrayWidth(); k++ ) {
                    for( int l = 0; l < tet->getArrayHeight(); l++ ) {
                        writeLog( LOG_VERBOSE, "copying... [%d, %d]", yA, xA );

                        // This is dirty and temporary.
                        // TODO: exit cleanly
                        if( xA < 0 ) { throw -2; }

                        if( check[l][k].doesExist() ) {
                            grid->set( yA+k, xA+l, check[l][k] );
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

Tetromino* GameState::getRandomPiece( ALLEGRO_BITMAP* blockIn ) {
    srand( time( NULL ) );
    int rNum = rand() % 6;

    switch( rNum ) {
        case 0:
            return new Tetromino( Tetromino_Type::I_BLOCK, blockIn );
        case 1:
            return new Tetromino( Tetromino_Type::O_BLOCK, blockIn );
        case 2:
            return new Tetromino( Tetromino_Type::L_BLOCK, blockIn );
        case 3:
            return new Tetromino( Tetromino_Type::J_BLOCK, blockIn );
        case 4:
            return new Tetromino( Tetromino_Type::T_BLOCK, blockIn );
        case 5:
            return new Tetromino( Tetromino_Type::S_BLOCK, blockIn );
        case 6:
            return new Tetromino( Tetromino_Type::Z_BLOCK, blockIn );
        default:
            writeLog( LOG_ERROR, "Invalid piece selected! Defaulting to I-Block." );
            return new Tetromino( Tetromino_Type::I_BLOCK, blockIn );
    }
}

bool GameState::render() { 
    //writeLog( LOG_VERBOSE, "render" );

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

    //writeLog( LOG_VERBOSE, "about to draw" );
    // Draw the grid
    for( int i = 0; i < 10; i++ ) {
        for( int j = 0; j < 20; j++ ) {
            //writeLog( LOG_VERBOSE, "checking if exists" );
            if( grid->get( j, i )->doesExist() ) {
                al_draw_tinted_bitmap( grid->get( j, i )->getBlock(), grid->get( j, i)->getColor(), 250 + i * 30, 1 + j * 30, 0 );
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