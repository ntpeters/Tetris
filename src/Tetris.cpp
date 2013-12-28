#include "Tetris.h"
#include "states/MenuState.h"
#include "util/SimpleLogger/simplog.h"
#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

/*
    Initialize game and all Allegro objects
*/
Tetris::Tetris() {
    // Initialize settings variables
    targetFPS       = 60.0;
    screenWidth     = 800;
    screenHeight    = 600;
    fontName        = "res/fnt/minecraftia.ttf";
    showFPS         = true;

    simplog.writeLog( LOG_VERBOSE, "Target FPS: %.2f", targetFPS );
    simplog.writeLog( LOG_VERBOSE, "Screen Width: %d", screenWidth );
    simplog.writeLog( LOG_VERBOSE, "Screen Height: %d", screenHeight );
    simplog.writeLog( LOG_VERBOSE, "Font Name: %s", fontName );
    simplog.writeLog( LOG_VERBOSE, "Display FPS set to '%s'", showFPS ? "true" : "false" );

    // Begin initializing Allegro objects
    display        = NULL;
    main_queue     = NULL;
    input_queue    = NULL;
    font18         = NULL;
    timer          = NULL;

    // Initialize Allegro
    if( !al_init() ) {
        simplog.writeLog( LOG_FATAL, "Failed to initialize Allegro!" );
        throw -1;
    } else {
        simplog.writeLog( LOG_DEBUG, "Allegro successfully initiallized" );
    }
 
    // Create the display
    display = al_create_display( screenWidth, screenHeight);
    if( !display ) {
        simplog.writeLog( LOG_FATAL, "Failed to create display!" );
        throw -1;
    } else {
        simplog.writeLog( LOG_DEBUG, "Display created successfully" );
    }

    // Initialize the keyboard
    if( !al_install_keyboard() ) {
        simplog.writeLog( LOG_FATAL, "Failed to initialize the keyboard!" );
        throw -1;
    } else {
        simplog.writeLog( LOG_DEBUG, "Keyboard initialized successfully" );
    }

    // Initialize the mouse
    if( !al_install_mouse() ) {
        simplog.writeLog( LOG_FATAL, "Failed to initialize the mouse!" );
        throw -1;
    } else {
        simplog.writeLog( LOG_DEBUG, "Mouse initialized successfully" );
    }

    // Create the main event queue
    main_queue = al_create_event_queue();
    if( !main_queue ) {
        simplog.writeLog( LOG_FATAL, "Failed to create main event queue!" );
        throw -1;
    } else {
        simplog.writeLog( LOG_DEBUG, "Main event Queue created susscessfully" );
    }

    // Create the input event queue
    input_queue = al_create_event_queue();
    if( !input_queue ) {
        simplog.writeLog( LOG_FATAL, "Failed to create input event queue!" );
        throw -1;
    } else {
        simplog.writeLog( LOG_DEBUG, "Input event Queue created susscessfully" );
    }

    // Register the display with the event queue
    al_register_event_source( main_queue, al_get_display_event_source( display ) );
    simplog.writeLog( LOG_VERBOSE, "Display event registered" );

    // Register the keyboard with the event queue
    al_register_event_source( input_queue, al_get_keyboard_event_source() );
    simplog.writeLog( LOG_VERBOSE, "Keyboard event registered" );

    // Register the mouse with the event queue
    al_register_event_source( input_queue, al_get_mouse_event_source() );
    simplog.writeLog( LOG_VERBOSE, "Mouse event registered" );

    // Initialize Allegro's image addon for handling images
    if( !al_init_image_addon() ) {
        simplog.writeLog( LOG_FATAL, "Failed to initialize image addon!" );
        throw -1;
    } else {
        simplog.writeLog( LOG_VERBOSE, "Image addon initialized" );
    }

    // Initialize Allegro's primitives addon for handling images
    if( !al_init_primitives_addon() ) {
        simplog.writeLog( LOG_FATAL, "Failed to initialize primitives addon!" );
        throw -1;
    } else {
        simplog.writeLog( LOG_VERBOSE, "Primitives addon initialized" );
    }

    // Initialize Allegro's font addon for handling fonts
    al_init_font_addon();
    simplog.writeLog( LOG_VERBOSE, "Font addon initialized" );

    // Initialize Allegro's TTF addon for handling TTF fonts
    if( !al_init_ttf_addon() ) {
        simplog.writeLog( LOG_FATAL, "Failed to initialize TTF addon!" );
        throw -1;
    } else {
        simplog.writeLog( LOG_VERBOSE, "TTF addon initialized" );
    }

    // Load a size 18 font
    font18 = al_load_font( fontName, 18, 0 );
    if( !font18 ) {
        simplog.writeLog( LOG_FATAL, "Failed to load font '%s' at size %d!", fontName, 18 );
        throw -1;
    } else {
        simplog.writeLog( LOG_DEBUG, "Font '%s' loaded at size %d", fontName, 18 );
    }

    // Load a size 12 font
    font12 = al_load_font( fontName, 12, 0 );
    if( !font12 ) {
        simplog.writeLog( LOG_FATAL, "Failed to load font '%s' at size %d!", fontName, 12 );
        throw -1;
    } else {
        simplog.writeLog( LOG_DEBUG, "Font '%s' loaded at size %d", fontName, 12 );
    }

    // Create a timer to cap the game FPS
    timer = al_create_timer( 1.0 / targetFPS );
    if( !timer ) {
        simplog.writeLog( LOG_FATAL, "Failed to create timer with resolution of %.2f seconds!", 1.0 / targetFPS );
        throw -1;
    } else {
        simplog.writeLog( LOG_VERBOSE, "Timer created with resolution of %.2f seconds", 1.0 / targetFPS );
    }

    // Register the timer with the event queue
    al_register_event_source( main_queue, al_get_timer_event_source( timer ) );
    simplog.writeLog( LOG_VERBOSE, "Timer event registered" );

    // Clear the screen to black
    al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

    // Push menu state onto the stack
    states = new std::stack<BaseState*>();
    states->push( new MenuState( display, input_queue, states ) );
}

/*
    Free all Allegro objects
*/
Tetris::~Tetris() {
    al_destroy_display( display );
    simplog.writeLog( LOG_VERBOSE, "Display destroyed" );

    al_destroy_event_queue( main_queue );
    simplog.writeLog( LOG_VERBOSE, "Main event queue destroyed" );

    al_destroy_event_queue( input_queue );
    simplog.writeLog( LOG_VERBOSE, "Input event queue destroyed" );

    al_destroy_timer( timer );
    simplog.writeLog( LOG_VERBOSE, "Timer destroyed" );

    al_destroy_font( font18 );
    simplog.writeLog( LOG_VERBOSE, "Font destroyed" );

    simplog.writeLog( LOG_DEBUG, "All game objects destroyed" );
}

/*
    Begin game execution
*/
void Tetris::play() {
    simplog.writeLog( LOG_INFO, "Tetris started successfully!" );

    // Start the timer
    al_start_timer( timer );
    simplog.writeLog( LOG_VERBOSE, "Timer started" );

    // Run loop variables
    bool done = false;
    bool redraw = true;
    double lastTime = al_get_time();
    double currentFPS = 0.0;
    int frames_done = 1;
    ALLEGRO_EVENT event;

    // Run loop
    while( !done ) {
        // Wait for an event to occur
        al_wait_for_event( main_queue, &event );

        // Redraw only when the timer event is triggered to cap FPS
        if( event.type == ALLEGRO_EVENT_TIMER ) {
            redraw = true;
        } else if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
            done = true;
        }

        // Get current time
        double currentTime = al_get_time();

        // Calculate delta time
        double delta = currentTime - lastTime;

        // Calculate current FPS
        if( delta >= 1.0 ) {
            currentFPS = frames_done / delta;
    
            frames_done = 0;
            lastTime = currentTime;
        }

        // Redraw if the timer was triggered, and the event queue is empty
        if( redraw && al_is_event_queue_empty( main_queue ) ) {
            redraw = false;

            // Update and render the current state
            bool updateOkay = states->top()->update( delta );
            bool renderOkay = states->top()->render();

            // Check if update and render completed okay for the current state
            if( !updateOkay || !renderOkay ) {
                // Delete the current state and pop if off the stack
                delete states->top();
                states->pop();

                // If there are no states left, end the run loop
                if( states->empty() ) {
                    done = true;
                }
            }

            // Print the FPS in the upper left corner
            if( showFPS ) {
                al_draw_textf( font12, al_map_rgb( 255, 255, 255 ), 0, 0, ALLEGRO_ALIGN_LEFT, "FPS: %.2f", currentFPS );
            }

            // Flip the display
            al_flip_display();
        }

        // Increment the current frames total
        frames_done++;
    }
}
