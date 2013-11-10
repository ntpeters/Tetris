#pragma once
#include "Block.h"
#include "Tetromino_Type.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>

class Tetromino {
public:
	Tetromino( Tetromino_Type type );
	Tetromino( Tetromino_Type type, ALLEGRO_BITMAP* blockIn );
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
	std::vector<std::vector<Block>> getBlocks();
	int getArrayWidth();
	int getArrayHeight();

protected:
	int decide_array_size( Tetromino_Type type );
	void init_block_array( Tetromino_Type type );
	//Block** blocks;
	std::vector<std::vector<Block>> blocks;
	int array_size;
	ALLEGRO_COLOR block_color;
	float x;
	float y;
};