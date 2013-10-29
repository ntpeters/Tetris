#pragma once
#include "BaseState.h"
#include <allegro5/allegro.h>

class GameState : public BaseState {
public:
	GameState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn );
	~GameState();
	bool update( double delta );
	bool render();
};