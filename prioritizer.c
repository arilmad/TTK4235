#include "prioritizer.h"

int prioritized_floor(int current_floor, int dir)
{

	//Scaling to make dir respond to BUTTON_CALL_UP and BUTTON_CALL_DOWN.
	if (dir == 1){
		dir = 0;
	}
	else{
		dir = 1;
	}

	//Internal orders or external orders in corresponding direction are always prioritized.
	if (get_order(current_floor, 2) || get_order(current_floor, dir))
	{
		return 1;
	}

	if (get_order(current_floor, !dir) && orders_ahead(current_floor, dir) == -1)
	{
		return 1;
	}
	return 0;
	
}

