#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "Block.h"

class Grid {
public:
	Grid( ALLEGRO_BITMAP* bmpImgIn );
	~Grid();
	void set( int x, int y, Block blockIn );
	Block* get( int x, int y );

private:
	std::vector<std::vector<Block>> grid;
};