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

typedef struct {
    uint8_t init;
    uint32_t tickCount;
} Stopwatch_t;

void init(Stopwatch_t* p_sw) {
    p_sw->init = 1;
    p_sw->tickCount = 0;
}

void init(Stopwatch_t* p_sw) {
    p_sw->init = 0;
}

#endif
