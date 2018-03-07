#ifndef __ORDER_HANDLING_H__
#define __ORDER_HANDLING_H__

#include <stdio.h>
#include "elev.h"



/**
Returns 1 if given floor has any active orders.
@param floor	Floor to get orders from.
@return			1 if active orders on given floor, 0 otherwise.
*/
int get_order_from_floor(int floor);


/**
Gets order from given floor and button.
@param floor	Floor to get order from.
@param button	Button to get order from.
@return			1 if order on button, 0 otherwise.
*/
int get_order(int floor, int button);



/**
Polls input channels to look for orders.
Sets corresponding button lamps to 1.
*/
void receive_orders(void);


/**
Looks for pending orders from bottom floor and up.
@return	Floor num from 0-3 if order is found. -1 otherwise.
*/
int pending_orders(void);


/**
Clears orders at given floor.
@param	Floor to clear orders from.
*/
void clear_orders_at_floor(int floor);

/**
Clears all the orders in the orders matrix.
*/
void clear_all_orders(void);


/**
Looks for orders ahead of the elevator relative to current direction and position.
@param current_floor 	Current floor.
@param dir				Elevator direction.
@return					Non-zero if order found in elevator's direction. -1 otherwise.
*/
int orders_ahead(int current_floor, int dir);


#endif	//ifndef __ORDER_HANDLING_H__