static state_t current_state = INIT;
static state_t previous_state;
static moving_state_t moving_state;
static clock_t reference;
int timeout = 3;

void fsm (int stop_button, int current_floor, int door_open, int current_dir) {
	if(stop_button){
		current_state = STOP_BUTTON;
	}
	switch(current_state) {
		case INIT:
			initialize_lift();
			current_state = STANDBY;
			break;

		case STANDBY:
			int requested_floor = pending_orders();
			if (requested_floor != -1){
				current_state = MOVING;
				move_to_floor(current_floor, requested_floor);
			}
			break;


		case STOP_BUTTON:

			break;
		case MOVING:
			if(current_floor == -1){
				break;
			}
			if(prioritized_floor(current_floor, current_dir)){
				current_state = WAITING;
				elev_set_motor_direction(DIRN_STOP);
				reference = clock();
				elev_set_door_open_lamp(1);
				clear_order(current_floor);
			}
			break;

		case WAITING:
			if (timer(timeout, reference)){
				elev_set_door_open_lamp(0);
			}
			if (door_open){
				break;
			}
			if (pending_orders() == -1){
				current_state = STANDBY;
				break;
			}

			int requested_floor = orders_ahead(current_floor, current_dir) + 1;

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
			break;
	}
}
