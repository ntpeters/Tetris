#include <stdio.h>
#include <string>
#include <allegro5/allegro_native_dialog.h>
#include "Tetris.h"
#include "util/simplog.h"

const char* version = "Development Build";

// Logger settings
bool keepLogs       = false;
const char* logFile = "tetris.log";
int logLevel        = LOG_VERBOSE;
bool silent         = false;

// Prototypes
void initLogger();

/*
    Creates and starts a new instance of Tetris.
    Displays an error message for any exceptions thrown.
*/
int main( int argc, char **argv ) {
    // Initialize the logger
    initLogger();

    writeLog( LOG_INFO, "Starting Tetris - Version: %s", version );

    // Try to create a new Tetris game
    try {
        Tetris *game = new Tetris();
        game->play();
        delete game;
    } catch( int err ) {
        // Display error message box
        al_show_native_message_box( al_get_current_display(), 
                                    "Tetris Error", 
                                    ( "Error Code: " + std::to_string( err ) ).c_str(), 
                                    "An unrecoverable error has occured.  See log for details.",
                                    NULL,
                                    ALLEGRO_MESSAGEBOX_ERROR );
        return err;
    }

    return 0;
}

void initLogger() {
    // Set logfile name
    setLogFile( logFile );

    // Flush the logfile
    if( !keepLogs ) {
        flushLog();
    }

    // Set the level of logger output
    setLogDebugLevel( logLevel );

    // Suppresses log output to stdout when true
    setLogSilentMode( silent );
}