/*
     A very basic logger for output of messages at various logging levels
     with date/time stamp to standard out and a defined log file.

     Author: Nate Peterson
     Created: June 2013
     Last Updated: Oct 2013
*/

#ifndef LOG_H
#define LOG_H

// Define logging levels
#define LOG_FATAL	-2
#define LOG_ERROR	-1
#define LOG_INFO	0
#define LOG_WARN	1
#define LOG_DEBUG	2
#define LOG_VERBOSE	3

#include <stdbool.h>

// Public functions
void writeLog( int loglvl, const char* str, ... );
void setDebugLevel( int level );
void setLogFile( const char* file );
void setSilentMode( bool silent );
void flushLog();

// Private functions
static char* getDateString();

#endif