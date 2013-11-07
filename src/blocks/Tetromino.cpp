#include "Tetromino.h"
#include "../util/simplog.h"
#include "Tetromino_Type.h"

Tetromino::Tetromino( Tetromino_Type type ) {
    x = 280;
    y = 31;

    if( type == Tetromino_Type::I_BLOCK || type == Tetromino_Type::O_BLOCK ) {
        array_size = 4;
    } else {
        array_size = 3;
    }

    init_block_array();

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

            blocks[0][1].toggleExists();
            blocks[0][2].toggleExists();
            blocks[1][1].toggleExists();
            blocks[1][2].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino O-Block created" );
            break;
        case Tetromino_Type::L_BLOCK:
            block_color = al_map_rgb( 255, 127, 0 );

            blocks[0][1].toggleExists();
            blocks[1][1].toggleExists();
            blocks[2][1].toggleExists();
            blocks[2][2].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino L-Block created" );
            break;
        case Tetromino_Type::J_BLOCK:
            block_color = al_map_rgb( 0, 0, 255 );

            blocks[0][1].toggleExists();
            blocks[1][1].toggleExists();
            blocks[2][1].toggleExists();
            blocks[2][0].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino J-Block created" );
            break;
        case Tetromino_Type::T_BLOCK:
            block_color = al_map_rgb( 128, 0, 128 );

            blocks[0][1].toggleExists();
            blocks[1][0].toggleExists();
            blocks[1][1].toggleExists();
            blocks[1][2].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino T-Block created" );
            break;
        case Tetromino_Type::S_BLOCK:
            block_color = al_map_rgb( 0, 255, 0 );

            blocks[0][2].toggleExists();
            blocks[0][1].toggleExists();
            blocks[1][1].toggleExists();
            blocks[1][0].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino S-Block created" );
            break;
        case Tetromino_Type::Z_BLOCK:
            block_color = al_map_rgb( 255, 0, 0 );

            blocks[0][0].toggleExists();
            blocks[0][1].toggleExists();
            blocks[1][1].toggleExists();
            blocks[1][2].toggleExists();

            writeLog( LOG_VERBOSE, "Tetromino Z-Block created" );
            break;
        default:
            writeLog( LOG_FATAL, "Invalid tetromino type provided!" );
    }
}

Tetromino::~Tetromino() {

}

void Tetromino::init_block_array() {
    blocks = new Block*[array_size];
    for( int i = 0; i < array_size; i++ )
        blocks[i] = new Block[array_size];

    writeLog( LOG_VERBOSE, "Tetromino array initialized" );
}

void Tetromino::rotateLeft() {

}

void Tetromino::rotateRight() {

}

void Tetromino::moveLeft( double delta ) {
    x -= 30 * delta;
}

void Tetromino::moveRight( double delta ) {
    x += 30 * delta;
}

void Tetromino::moveDown( double delta ) {
    y += 60 * delta;
}

void Tetromino::update( double delta ) {
    y += 30 * delta;
}

void Tetromino::draw() {
    for( int i = 0; i < array_size; i++ ) {
        for( int j = 0; j < array_size; j++ ) {
            if( blocks[i][j].doesExist() ) {
                al_draw_tinted_bitmap( blocks[i][j].getBlock(), block_color, x + j * 30, y + i * 30, 0 );
            }
        }
    }
}