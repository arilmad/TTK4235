#include "prioritizer.h"

int prioritized_floor(int current_floor, int dir)
{
	//Buttons and motor operate with different dir indexing. Scaling dir from motor to buttons for further use

	//The function suggested_stop returns 2 if the lift has an active order made inside itself,
	//0 if it has an active order from reached floor in UP dir
	//1 if there is and active order from reached floor in DOWN dir
	//-1 elsewise


	if(current_floor == 3 || current_floor == 0 || get_order(current_floor, 2))
	{
		return 1;
	}

	if (get_order(current_floor, dir))
	{
		return 1;
	}
	//else{printf("FLOOR_ORDER FEILER");}


	if (get_order(current_floor, !dir) && (!(orders_ahead(current_floor, dir))))
	{
		return 1;
	}
	return 0;
}

int orders_ahead(int current_floor, int dir){


	//Returns nearest floor to which the elevator is ordered. -1 elsewise

	//If elevator is either at top or bottom floor, it will request to stop

	//If direction is UP, elevator checks lights in floors above. 
	if (dir == 0)
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
	else if (dir == 1){
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