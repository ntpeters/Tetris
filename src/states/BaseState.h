#pragma once
#include <allegro5/allegro.h>

class BaseState {
public:
	BaseState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn );
	virtual ~BaseState();
	virtual bool update( double delta ) = 0;
	virtual bool render() = 0;

protected:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* event_queue;
};