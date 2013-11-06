#pragma once
#include "Block.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Tetromino {
public:
	Tetromino();
	~Tetromino();
	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;
	void moveLeft();
	void moveRight();
	void moveDown( double delta );
	virtual void draw() = 0;

protected:
	Block* block;
	float x;
	float y;
};