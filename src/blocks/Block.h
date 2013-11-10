#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Block {
public:
	Block();
	~Block();
	ALLEGRO_BITMAP* getBlock();
	ALLEGRO_COLOR getColor();
	void setColor( ALLEGRO_COLOR colorIn );
	bool doesExist();
	void toggleExists();

private:
	ALLEGRO_BITMAP* block;
	ALLEGRO_COLOR block_color;
	bool exists;
};