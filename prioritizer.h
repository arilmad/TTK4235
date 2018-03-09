#ifndef __PRIORITIZER_H__
#define __PRIORITIZER_H__

#include "order_handling.h"


/**
Decides if the elevator stops at current floor.
@param current_floor 	Current floor
@param dir				Elevator direction
@return					Non-zero to stop, 0 otherwise
*/
int prioritized_floor(int current_floor, int dir);


#endif	// #ifndef __PRIORITIZER_H__