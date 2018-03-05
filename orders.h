#ifndef __ORDERS_H__
#define __ORDERS_H__

#include <stdio.h>
#include "elev.h"

/*
Gets the order from a given floor and button.
@param floor	Floor to get order from
@param button	Button to get order from
@return			Non-zero if order on button, 0 otherwise.
*/
int get_order(int floor, int button);


int get_order_from_floor(int floor);


/*
Polls input channels to look for orders.
*/
void receive_orders(void);


/*
Looks for pending orders
@return	Num of firs pending order it hits, 0 otherwise.
*/
int pending_orders(void);


/*
Clear order on given floor
@param	Floor to clear orders from.
*/
void clear_order(int floor);

/*

*/
void clear_all_orders(void);


/*
Clears all orders
*/
void clear_all_orders(void);

/*
Initialization of the elevator.
Elevator moves upwards and stops at nearest floor.
@return Current floor
*/
int initialize_lift(void);


/*
Starte the motor.
@param current_floor	Elevators current floor
@param desired_floor	The requested floor to go to
*/
void move_to_floor(double current_floor, int desired_floor);



#endif	//ifndef __ORDERS_H__