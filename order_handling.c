#include "order_handling.h"

static int ORDERS[N_FLOORS][N_BUTTONS] = 
{
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
};


int get_order_from_floor(int floor){

	for (int button = 0; button < N_BUTTONS; button++){

		if(get_order(floor, button)){
			return 1;
		}
	}
	return 0;
}


int get_order(int floor, int button){
	return ORDERS[floor][button];
}


void receive_orders(void){

	for (int floor = 0; floor < N_FLOORS; floor++){
		for (int button = 0; button < N_BUTTONS; button++){

			if ((floor == (N_FLOORS - 1)) && (button == 0)) continue;
			else if ((floor == 0) && (button == 1)) continue;
			else
			{			
				if(elev_get_button_signal(button, floor))
				{
					ORDERS[floor][button] = 1;
					elev_set_button_lamp(button, floor, 1);
				}
			}
		}
	}
}


int pending_orders(void){

	for (int floor = 0; floor < N_FLOORS; floor++){

		for (int button = 0; button < N_BUTTONS; button++){

			if(ORDERS[floor][button])
				return floor;		
		}
	}

	return -1;
}


void clear_orders_at_floor(int floor){

	for (int button = 0; button < N_BUTTONS; button++){

		if ((floor == (N_FLOORS - 1)) && (button == 0)) continue;
		else if ((floor == 0) && (button == 1)) continue;
		else{
			ORDERS[floor][button] = 0;
			elev_set_button_lamp(button, floor, 0);
		}
	}
}


void clear_all_orders(void)
{
	for (int floor = 0; floor < N_FLOORS; floor++)
		clear_orders_at_floor(floor);
}


int orders_ahead(int current_floor, int dir){

	//If direction is UP, elevator checks lights in floors above. 
	if (dir == 1){
		for (int above = current_floor+1; above < N_FLOORS; above++){
			for (int button = 0; button < N_BUTTONS ; button++){
				if (get_order(above, button))
					return above;
			}
		}
	}

	////If direction is DOWN, elevator checks lights in floors below.
	else if (dir == -1){
		for (int below = current_floor-1; below > -1; below--){
			for (int button = 0; button < N_BUTTONS ; button++){
				if (get_order(below, button))
					return below;
			}
		}
	}
	return -1;
}