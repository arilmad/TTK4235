#include "prioritizer.h"

int prioritized_floor(int current_floor, int dir)
{
	
	//Scaling to make dir respond to BUTTON_CALL_UP and BUTTON_CALL_DOWN
	if (dir == 1){
		dir = 0;
	}
	else{
		dir = 1;
	}



	if (get_order(current_floor, 2))
	{
		return 1;
	}

	if (get_order(current_floor, dir))
	{
		return 1;
	}
	//else{printf("FLOOR_ORDER FEILER");}


	if (get_order(current_floor, !dir) && (!(orders_ahead(current_floor, dir) + 1)))
	{
		return 1;
	}
	return 0;
}

int orders_ahead(int current_floor, int dir){


	//Returns nearest floor to which the elevator is ordered. -1 elsewise

	//If direction is UP, elevator checks lights in floors above. 
	if (dir == 1)
	{
		for (int above = current_floor+1; above < N_FLOORS; above++)
		{
			for (int button = 0; button < N_BUTTONS ; button++)
			{
				if (get_order(above, button))
				{
					return above;
				}
			}
		}
	}

	////If direction is DOWN, elevator checks lights in floors below.
	else if (dir == -1){
		for (int below = current_floor-1; below > -1; below--)
		{
			for (int button = 0; button < N_BUTTONS ; button++)
			{
				if (get_order(below, button))
				{
					return below;
				}
			}
		}
	}
	return -1;
}