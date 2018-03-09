#ifndef __timer_H__
#define __timer_H__

#include <stdlib.h>
#include <time.h>


/**
Timer for the door
@param count_s seconds to set the timer
@param reference reference time for the timer
@return non-zero if the time has elapsed, zero otherwise
*/
int timer_has_time_elapsed(int count_s, clock_t reference);


#endif	//#ifndef __timer_H__