#include "MenuState.h"

MenuState::MenuState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn ) : BaseState( displayIn, event_queueIn, statesIn ) {
    const char* fontName        = "res/fnt/minecraftia.ttf";

    // Load a size 18 font
    font18 = al_load_font( fontName, 18, 0 );
    if( !font18 ) {
        writeLog( LOG_FATAL, "Failed to load font '%s' at size %d!", fontName, 18 );
        throw -1;
    } else {
        writeLog( LOG_DEBUG, "Font '%s' loaded at size %d", fontName, 18 );
    }

    writeLog( LOG_DEBUG, "New menu state created" );
}

MenuState::~MenuState() {
    writeLog( LOG_DEBUG, "Menu state destroyed" );
}

bool MenuState::update( double delta ) {
    ALLEGRO_EVENT ev;
    ALLEGRO_TIMEOUT timeout;
    al_init_timeout(&timeout, 0.01);

    bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
 
    if(get_event) {
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
            states->push( new GameState( display, event_queue, states ) );
        }
    }

    return true;
}

bool MenuState::render() { 
 
    // Clear screen to purple
    al_clear_to_color( al_map_rgb( 50, 10, 70) );

    // Draw menu text
    al_draw_text( font18, al_map_rgb( 255, 255, 255 ), 800/2, (600/4),ALLEGRO_ALIGN_CENTRE, "This is the menu!");

    return true;
}