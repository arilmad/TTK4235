#include "fsm.h"

static state_t current_state = INIT;
static clock_t start_clock_reference;
int n_seconds = 3;
int requested_floor;
int prev_floor;
int prev_dir;

double in_between_floors;

void fsm (int stop_button, int current_floor, int door_open, int current_dir) {

	receive_orders();

	double current_position = (double)current_floor;

	if(stop_button){
		current_state = STOP_BUTTON;
	}


	switch(current_state) {


	
		case INIT:
		//Case purpose: Initialize elevator at program startup

			initialize_lift();
			current_state = STANDBY;
			printf("Entering standby from init\n");
			break;



		case STANDBY:
		//Case purpose: Elevator has doors closed and no active orders. 

			//pending_orders returns -1 if no orders are placed.
			requested_floor = pending_orders();


			//Elevator calculates it's position if stop button is pressed in between floors.
			if (current_floor == -1){

				if(prev_dir == 0){
					in_between_floors = prev_floor + 0.5;
				}
				else{
					in_between_floors = prev_floor - 0.5;
				}
				current_position = in_between_floors;
			}


			else if (requested_floor == current_floor){
				current_state = DOOR_OPEN;
				printf("Entering door_open from standby\n");
				start_clock_reference; = clock();
				elev_set_door_open_lamp(1);
				break;
			}


			if (requested_floor != -1){
				current_state = MOVING;
				printf("Entering moving from standby\n");
				move_to_floor(current_position, requested_floor);
			}

			break;



		case STOP_BUTTON:
		//Case purpose: Stop button has been pressed. Elevator stops immediately and clears all orders.

			elev_set_motor_direction(DIRN_STOP);
			elev_set_stop_lamp(1);
			clear_all_orders();

			while (elev_get_stop_signal()){continue;}
			elev_set_stop_lamp(0);


			if (elev_get_floor_sensor_signal() != -1)
			{
				start_clock_reference; = clock();
				elev_set_door_open_lamp(1);
				current_state = DOOR_OPEN;
				printf("Entering door_open from stop_button\n");
				break;
			}

			current_state = STANDBY;
			printf("Entering standby from stop_button\n");
			break;



		case MOVING:
		//Case purpose: Elevator is on it's way to a destination. Will exit state if the prioritizing 
		//algorithm indicates that a stop is desired at current floor.

			if (current_floor != -1){

				elev_set_floor_indicator(current_floor);
				prev_floor = current_floor;
				prev_dir = current_dir;


				if (prioritized_floor(current_floor, current_dir)){

					elev_set_motor_direction(DIRN_STOP);
					start_clock_reference; = clock();
					elev_set_door_open_lamp(1);
					clear_order(current_floor);

					current_state = DOOR_OPEN;
					printf("Entering door_open from moving\n");
				}
			}


			break;



		case DOOR_OPEN:
		//Case purpose: Elevator is waiting for the doors to close before eventually deciding whether to 
		//continue up, down or go to STANDBY depending on active orders.

			if (timer(n_seconds, start_clock_reference;)){
				elev_set_door_open_lamp(0);
			}

			if (door_open){
				clear_order(current_floor);
				break;
			}

			//If there are no active orders, elevator returns to STANDBY.
			if (pending_orders() == -1){
				current_state = STANDBY;
				printf("Entering standby from door_open\n");
				break;
			}


			//If orders_ahead returns anything above -1, the elevator has interest in continuing in current dir.
			if (orders_ahead(current_floor, current_dir) != -1){

				if (orders_ahead(current_floor, current_dir) != -1){
					elev_set_motor_direction(current_dir);
				}
				else {
					elev_set_motor_direction(-current_dir);
				}
			}

			current_state = MOVING;
			printf("Entering moving from door_open\n");
			break;
	}
}
