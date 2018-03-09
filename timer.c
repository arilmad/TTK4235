#include "timer.h"


int timer_has_time_elapsed(int count_s, clock_t reference){
	
	clock_t new_time = clock();

	if (((new_time - reference)/CLOCKS_PER_SEC) >= count_s)
		return 1;
	
	return 0;
}