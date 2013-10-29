#pragma once
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class Tetris {
public:
	Tetris();
	~Tetris();
	void play();;

private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_FONT *font12;
	ALLEGRO_FONT *font18;
	ALLEGRO_TIMER *timer;
	double FPS;
	int screenWidth;
	int screenHeight;
	const char* fontName;
	bool showFPS;
};