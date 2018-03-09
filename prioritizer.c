#include "prioritizer.h"

int prioritized_floor(int current_floor, int dir){

	int dir_button;

	//Scaling to make dir correspond to BUTTON_CALL_UP and BUTTON_CALL_DOWN.
	if (dir == 1)
		dir_button = 0;
	else
		dir_button = 1;


	//Internal orders or external orders in elevator's current direction are always prioritized.
	if (get_order(current_floor, 2) || get_order(current_floor, dir_button))
		return 1;

	//If there are no active orders from floors ahead of elevator, it should request to stop at current floor.
	if (orders_ahead(current_floor, dir) == -1)
		return 1;

	return 0;
}

