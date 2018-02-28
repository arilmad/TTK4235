#include "fsm.h"

static state_t current_state = INIT;
static clock_t reference;
int timeout = 3;
int requested_floor;
int prev_floor;
int prev_dir;

//used to identify elevator's position when stopped in between floors.
//HUSK Å ENDRA NAVN FØR FAT!!!!!!!!!!
double trouble;

void fsm (int stop_button, int current_floor, int door_open, int current_dir) {

	receive_orders();

	double floor = (double)current_floor;

	if(stop_button){
		current_state = STOP_BUTTON;
	}

	switch(current_state) {

		case INIT:

			initialize_lift();
			current_state = STANDBY;
			printf("Entering standby from init\n");
			break;



		case STANDBY:

			requested_floor = pending_orders();

			if (current_floor == -1){

				if(prev_dir == 0){
					trouble = prev_floor + 0.5;
				}

				else{
					trouble = prev_floor - 0.5;
				}

				floor = trouble;
			}

			else if (requested_floor == current_floor){
				current_state = DOOR_OPEN;
				printf("Entering door_open from standby\n");
				reference = clock();
				elev_set_door_open_lamp(1);
				break;
			}

			if (requested_floor != -1){
				current_state = MOVING;
				printf("Entering moving from standby\n");
				move_to_floor(floor, requested_floor);
			}

			break;



		case STOP_BUTTON:
			elev_set_motor_direction(DIRN_STOP);
			elev_set_stop_lamp(1);
			clear_all_orders();

			while (elev_get_stop_signal()){continue;}
			elev_set_stop_lamp(0);

			if (elev_get_floor_sensor_signal() != -1)
			{
				reference = clock();
				elev_set_door_open_lamp(1);
				current_state = DOOR_OPEN;
				printf("Entering door_open from stop_button\n");
				break;
			}
			current_state = STANDBY;
			printf("Entering standby from stop_button\n");
			break;



		case MOVING:
			if(current_floor == -1){
				break;
			}
			else {
				elev_set_floor_indicator(current_floor);
				prev_floor = current_floor;
				prev_dir = current_dir;
			}

			if(prioritized_floor(current_floor, current_dir)){
				current_state = DOOR_OPEN;
				elev_set_motor_direction(DIRN_STOP);
				reference = clock();
				elev_set_door_open_lamp(1);
				clear_order(current_floor);
				printf("Entering door_open from moving\n");
			}
			break;



		case DOOR_OPEN:
			if (timer(timeout, reference)){
				elev_set_door_open_lamp(0);
			}
			if (door_open){
				clear_order(current_floor);
				break;
			}
			if (pending_orders() == -1){
				current_state = STANDBY;
				printf("Entering standby from door_open\n");
				break;
			}

			requested_floor = orders_ahead(current_floor, current_dir) + 1;

			if(requested_floor){
				if (current_dir == 0) {
					elev_set_motor_direction(DIRN_UP);
				}
				else if (current_dir == 1)
				{
					elev_set_motor_direction(DIRN_DOWN);
				}
			}

			else {
				if (current_dir == 1) {
					elev_set_motor_direction(DIRN_UP);
				}
				else if (current_dir == 0)
				{
					elev_set_motor_direction(DIRN_DOWN);
				}
			}

			current_state = MOVING;
			printf("Entering moving from door_open\n");
			break;
	}
}
