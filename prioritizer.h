#ifndef __PRIORITIZER_H__
#define __PRIORITIZER_H__

#include "elev.h"
#include "orders.h"
/**
Decides if the elevator stops at current floor.
@param current_floor 	Current floor
@param dir				Elevator direction
@return					Non-zero to stop, 0 otherwise
*/
int prioritized_floor(int current_floor, int dir);


/**
Looks for orders ahead of the elevator
@param current_floor 	Current floor
@param dir				Elevator direction
@return					Non-zero if order in elevators direction, -1 otherwise
*/
int orders_ahead(int current_floor, int dir);

#endif	// #ifndef __PRIORITIZER_H__