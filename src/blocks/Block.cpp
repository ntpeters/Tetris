#include "Block.h"
#include "../util/simplog.h"

Block::Block() {
	const char* bmpFile = "res/img/block2.png";

	block = al_load_bitmap( bmpFile );
    if( !block ) {
        writeLog( LOG_FATAL, "Failed to load bitmap!" );
        throw -1;
    } else {
        writeLog( LOG_VERBOSE, "Bitmap loaded successfully" );
    }

    exists = false;
}

Block::~Block() {
	// Free bitmap object
	al_destroy_bitmap( block );
	writeLog( LOG_VERBOSE, "Bitmap object destroyed" );
}

ALLEGRO_BITMAP* Block::getBlock() {
	return block;
}

ALLEGRO_COLOR Block::getColor() {
	return block_color;
}

void Block::setColor( ALLEGRO_COLOR colorIn ) {
	block_color = colorIn;
}

bool Block::doesExist() {
	return exists;
}

void Block::toggleExists() {
	exists = !exists;
}