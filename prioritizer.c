#include "prioritizer.h"

int prioritizer_prioritized_floor(int current_floor, int dir)
{

	int dir_button;

	//Scaling to make dir correspond to BUTTON_CALL_UP and BUTTON_CALL_DOWN.
	if (dir == 1){
		dir_button = 0;
	}

	else{
		dir_button = 1;
	}

	//Internal orders or external orders in corresponding direction are always prioritized.
	if (get_order(current_floor, 2) || get_order(current_floor, dir_button)){
		return 1;
	}

	//If there are no orders in current moving direction the it will prioritize button in oposite direction.
	if (get_order(current_floor, !dir_button) && orders_ahead(current_floor, dir_button) == -1){
		return 1;
	}

	return 0;
}

