#ifndef __ORDERS_H__
#define __ORDERS_H__

#include <stdio.h>
#include "elev.h"
#include "orders.h"

/*
Gets the order from a given floor and button.
@param floor	Floor to get order from
@param button	Button to get order from
@return			Non-zero if order on button, 0 otherwise.
*/
int get_order(int floor, int button);


/*
Polls input channels to look for orders.
*/
void receive_orders(void);


/*
Clear order on given floor
@param	Floor to clear orders from.
*/
void clear_order(int floor);

/*

*/
void clear_all_orders(void);


/*
Looks for pending orders
@return	Non-zero if there are any pending orders, 0 otherwise.
*/
int pending_orders(void);

#endif	//ifndef __ORDERS_H__