#include "Tetris.h"
#include "log.h"
#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*
    Initialize game and all Allegro objects
*/
Tetris::Tetris() {
    // Set logfile name
    setLogFile( "tetris.log" );

    // Flush the logfile (comment out to maintain a running log)
    flushLog();

    // Set the level of logger output
    setDebugLevel( LOG_DEBUG );

    // Initialize settings variables
    FPS             = 60.0;
    screenWidth     = 640;
    screenHeight    = 480;
    fontName        = "minecraftia.ttf";
    showFPS         = true;

    writeLog( LOG_VERBOSE, "Target FPS: %.2f", FPS );
    writeLog( LOG_VERBOSE, "Screen Width: %d", screenWidth );
    writeLog( LOG_VERBOSE, "Screen Height: %d", screenHeight );
    writeLog( LOG_VERBOSE, "Font Name: %s", fontName );
    writeLog( LOG_VERBOSE, "Display FPS set to '%s'", showFPS ? "true" : "false" );

    // Begin initializing Allegro objects
	display = NULL;
	event_queue = NULL;
    font18 = NULL;
    timer = NULL;

    // Initialize Allegro
 	if( !al_init() ) {
        writeLog( LOG_FATAL, "Failed to initialize Allegro!" );
        throw -1;
    } else {
        writeLog( LOG_DEBUG, "Allegro successfully initiallized" );
    }
 
    // Create the display
    display = al_create_display( screenWidth, screenHeight);
    if( !display ) {
        writeLog( LOG_FATAL, "Failed to create display!" );
        throw -1;
    } else {
        writeLog( LOG_DEBUG, "Display created successfully" );
    }

    // Initialize the keyboard
    if( !al_install_keyboard() ) {
        writeLog( LOG_FATAL, "Failed to initialize the keyboard!" );
        throw -1;
	} else {
        writeLog( LOG_DEBUG, "Keyboard initialized successfully" );
	}

    // Create the event queue
	event_queue = al_create_event_queue();
	if( !event_queue ) {
        writeLog( LOG_FATAL, "Failed to create event queue!" );
        throw -1;
	} else {
        writeLog( LOG_DEBUG, "Event Queue created susscessfully" );
	}

    // Register the display with the event queue
	al_register_event_source( event_queue, al_get_display_event_source( display ) );
    writeLog( LOG_VERBOSE, "Display event registered" );

    // Register the keyboard with the event queue
    al_register_event_source( event_queue, al_get_keyboard_event_source() );
    writeLog( LOG_VERBOSE, "Keyboard event registered" );

    // Initialize Allegro's font addon for handling fonts
    al_init_font_addon();
    writeLog( LOG_VERBOSE, "Font addon initialized" );

    // Initialize Allegro's TTF addon for handling TTF fonts
    al_init_ttf_addon();
    writeLog( LOG_VERBOSE, "TTF addon initialized" );

    // Load a size 18 font
    font18 = al_load_font( fontName, 18, 0 );
    writeLog( LOG_DEBUG, "Font '%s' loaded at size %d", fontName, 18 );

    // Load a size 12 font
    font12 = al_load_font( fontName, 12, 0 );
    writeLog( LOG_DEBUG, "Font '%s' loaded at size %d", fontName, 12 );

    // Create a timer to cap the game FPS
    timer = al_create_timer( 1.0 / FPS );
    writeLog( LOG_VERBOSE, "Timer created" );

    // Register the timer with the event queue
    al_register_event_source( event_queue, al_get_timer_event_source( timer ) );
    writeLog( LOG_VERBOSE, "Timer event registered" );

    // Clear the screen to black
    al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
}

/*
    Destroy all Allegro objects
*/
Tetris::~Tetris() {
    // Free all Allegro objects

	al_destroy_display( display );
    writeLog( LOG_VERBOSE, "Display destroyed" );

    al_destroy_event_queue( event_queue );
    writeLog( LOG_VERBOSE, "Event queue destroyed" );

    al_destroy_timer( timer );
    writeLog( LOG_VERBOSE, "Timer destroyed" );

    al_destroy_font( font18 );
    writeLog( LOG_VERBOSE, "Font destroyed" );

    writeLog( LOG_DEBUG, "All game objects destroyed" );
}

/*
    Begin game execution
*/
void Tetris::play() {
    writeLog( LOG_INFO, "Game started successfully!" );

    // Start the timer
    al_start_timer( timer );
    writeLog( LOG_VERBOSE, "Timer started" );

    // Run loop variables
    bool done = false;
    bool redraw = true;
    double old_time = al_get_time();
    double cur_fps = 0.0;
    int frames_done = 1;
    ALLEGRO_EVENT ev;

    // Run loop
    while( !done ) {
        // Wait for an event to occur
        al_wait_for_event( event_queue, &ev );

        // Redraw everytime the timer event is triggered
        if( ev.type == ALLEGRO_EVENT_TIMER ) {
            redraw = true;
        }

        // Calculate current FPS
        double cur_time = al_get_time();
        if( cur_time - old_time >= 1.0 ) {
            cur_fps = frames_done / ( cur_time - old_time );
    
            frames_done = 0;
            old_time = cur_time;
        }        

        if( redraw && al_is_event_queue_empty( event_queue ) ) {
            redraw = false;

            // Print the FPS in the upper left corner
            if( showFPS ) {
                al_draw_textf( font12, al_map_rgb( 255, 255, 255 ), 0, 0, ALLEGRO_ALIGN_LEFT, "FPS: %.2f", cur_fps );
            }

            // Flip the display and clear screen to black
            al_flip_display();
            al_clear_to_color( al_map_rgb( 0, 0, 0) );
        }

        // Increment the current frames total
        frames_done++;
    }
}