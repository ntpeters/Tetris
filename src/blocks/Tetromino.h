#pragma once
#include "Block.h"
#include "Tetromino_Type.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Tetromino {
public:
	Tetromino( Tetromino_Type type );
	~Tetromino();
	void rotateLeft();
	void rotateRight();
	void moveLeft( double delta );
	void moveRight( double delta );
	void moveDown( double delta );
	void update( double delta );
	void draw();
	int getX();
	int getY();
	void setX( int xIn );
	void setY( int yIn );
	Block** getBlocks();
	int getArrayWidth();
	int getArrayHeight();

protected:
	void init_block_array();
	Block** blocks;
	int array_size;
	ALLEGRO_COLOR block_color;
	float x;
	float y;
};