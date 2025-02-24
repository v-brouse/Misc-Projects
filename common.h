/*
 * Operating Systems: Three Easy Pieces (OSTEP)
 *
 * Modified by Drue Coles
 * 1. Renamed identifiers following C conventions.
 * 2. Added function documentation.
 * 3. Minor cosmetic edits.
 */

#ifndef __common_h__
#define __common_h__

#include <sys/time.h>
#include <sys/stat.h>
#include <assert.h>

// Returns number of seconds (with microsecond precision) 
// since the beginning of UNIX epoch.
double get_time() {
    struct timeval t; // see comments at end of file
    int rc = gettimeofday(&t, 0);
    assert(rc == 0);
    return (double) t.tv_sec + (double) t.tv_usec / 1e6;
}

// Loops for a given number of seconds.
void spin(int how_long) {
    double start = get_time();
    while ((get_time() - start) < (double) how_long); 
}

#endif // __common_h__


/************************** NOTES ABOUT TIMEVAL **************************
 
Declared in sys/time.h

Represents the time in microseconds since the beginning of the UNIX epoch.
The first field stores the number of seconds and the second field stores
the remaining fraction of a second. The field types are aliases (typedef)
for signed integers.

   struct timeval {
       time_t      tv_sec;     // seconds 
       suseconds_t tv_usec;    // microseconds 
   };


The second parameter denotes a struct with time zone information.

   gettimeofday(struct timeval *, struct tzp *);

************************** NOTES ABOUT TIMEVAL **************************/