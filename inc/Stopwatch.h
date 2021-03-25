/*

Provides time keeping for benchmarking.

Start - starts the stopwatch.
Stop - stops the stopwatch.
Reset - resets the stopwatch.
GetTime - returns the time in [smallest possible units]

*/

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdint.h>


void stopwatch_init( void );

void stopwatch_start( void );

void stopwatch_stop( void );

void stopwatch_reset( void );

int stopwatch_get_time( void );

#endif
