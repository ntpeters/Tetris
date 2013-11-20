#include "Tetromino.h"
#include "../util/simplog.h"
#include "Tetromino_Type.h"
#include <vector>

Tetromino::Tetromino( Tetromino_Type type ) 
: blocks( decide_array_size( type ), std::vector<Block>( decide_array_size( type ), Block() ) ) {
    x = 280;
    y = -29;

/*    if( type == Tetromino_Type::I_BLOCK || type == Tetromino_Type::O_BLOCK ) {
        array_size = 4;
    } else {
        array_size = 3;
    }*/

    init_block_array( type );
}

Tetromino::Tetromino( Tetromino_Type type, ALLEGRO_BITMAP* blockIn )
: blocks( decide_array_size( type ), std::vector<Block>( decide_array_size( type ), Block( blockIn ) ) ) {
    x = 280;
    y = -29;

/*    if( type == Tetromino_Type::I_BLOCK || type == Tetromino_Type::O_BLOCK ) {
        array_size = 4;
    } else {
        array_size = 3;
    }*/

    init_block_array( type );
}

Tetromino::~Tetromino() {

}

int Tetromino::decide_array_size( Tetromino_Type type ) {
    if( type == Tetromino_Type::I_BLOCK || type == Tetromino_Type::O_BLOCK ) {
        array_size = 4;
        return 4;
    } else {
        array_size = 3;
        return 3;
    }
}

void Tetromino::init_block_array( Tetromino_Type type ) {
        switch( type ) {
        case Tetromino_Type::I_BLOCK:
            block_color = al_map_rgb( 0, 255, 255 );

            blocks[0][1].toggleExists();
            blocks[1][1].toggleExists();
            blocks[2][1].toggleExists();
            blocks[3][1].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino I-Block created" );
            break;
        case Tetromino_Type::O_BLOCK:
            block_color = al_map_rgb( 255, 255, 0 );

            blocks[1][0].toggleExists();
            blocks[2][0].toggleExists();
            blocks[1][1].toggleExists();
            blocks[2][1].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino O-Block created" );
            break;
        case Tetromino_Type::L_BLOCK:
            block_color = al_map_rgb( 255, 127, 0 );

            blocks[0][1].toggleExists();
            blocks[1][1].toggleExists();
            blocks[2][0].toggleExists();
            blocks[2][1].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino L-Block created" );
            break;
        case Tetromino_Type::J_BLOCK:
            block_color = al_map_rgb( 0, 0, 255 );            

            blocks[0][0].toggleExists();
            blocks[0][1].toggleExists();
            blocks[1][1].toggleExists();
            blocks[2][1].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino J-Block created" );
            break;
        case Tetromino_Type::T_BLOCK:
            block_color = al_map_rgb( 128, 0, 128 );

            blocks[1][0].toggleExists();
            blocks[0][1].toggleExists();
            blocks[1][1].toggleExists();
            blocks[2][1].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino T-Block created" );
            break;
        case Tetromino_Type::S_BLOCK:
            block_color = al_map_rgb( 0, 255, 0 );

            blocks[2][0].toggleExists();
            blocks[1][0].toggleExists();
            blocks[1][1].toggleExists();
            blocks[0][1].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino S-Block created" );
            break;
        case Tetromino_Type::Z_BLOCK:
            block_color = al_map_rgb( 255, 0, 0 );

            blocks[0][0].toggleExists();
            blocks[1][0].toggleExists();
            blocks[1][1].toggleExists();
            blocks[2][1].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino Z-Block created" );
            break;
        default:
            writeLog( LOG_FATAL, "Invalid tetromino type provided!" );
    }

    // Set block colors
    for( int i = 0; i < array_size; i++ ) {
        for( int j = 0; j < array_size; j++ ) {
            blocks[i][j].setColor( block_color );
        }
    }
}

void Tetromino::rotateLeft() {

}

void Tetromino::rotateRight() {

}

void Tetromino::moveLeft( double delta ) {
    x -= 30;
}

void Tetromino::moveRight( double delta ) {
    x += 30;
}

void Tetromino::moveDown( double delta ) {
    y += 60;
}

void Tetromino::update( double delta ) {
    y += 30;
}

void Tetromino::draw() {
    for( int i = 0; i < array_size; i++ ) {
        for( int j = 0; j < array_size; j++ ) {
            if( blocks[i][j].doesExist() ) {
                al_draw_tinted_bitmap( blocks[i][j].getBlock(), block_color, x + i * 30, y + j * 30, 0 );
            } else {
                //al_draw_tinted_bitmap( blocks[i][j].getBlock(), al_map_rgb(255,0,255), x + i * 30, y + j * 30, 0 );
            }
        }
    }
}

int Tetromino::getX() {
    return x;
}

int Tetromino::getY() {
    return y;
}

void Tetromino::setX( int xIn ) {
    x = xIn;
}

void Tetromino::setY( int yIn ) {
    y = yIn;
}

std::vector<std::vector<Block>> Tetromino::getBlocks() {
    return blocks;
}

int Tetromino::getArrayWidth() {
    return array_size;
}

int Tetromino::getArrayHeight() {
    return array_size;
}