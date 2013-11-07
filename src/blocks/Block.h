#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Block {
public:
	Block();
	~Block();
	ALLEGRO_BITMAP* getBlock();
	bool doesExist();
	void toggleExists();

private:
	ALLEGRO_BITMAP* block;
	bool exists;
};