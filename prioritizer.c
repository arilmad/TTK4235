#include "prioritizer.h"

int prioritized_floor(int current_floor, int dir)
{
	//Buttons and motor operate with different dir indexing. Scaling dir from motor to buttons for further use

	//The function suggested_stop returns 2 if the lift has an active order made inside itself,
	//0 if it has an active order from reached floor in UP dir
	//1 if there is and active order from reached floor in DOWN dir
	//-1 elsewise
	int ordered_at_current_floor = (get_order(floor, 2) || get_order(floor, dir));

	if (ordered_at_current_floor)
	{
		return 1;
	}

	if (!(orders_ahead(current_floor, dir)))
	{
		return 1;
	}
	return 0;

}

int orders_ahead(int current_floor, int dir)
{

	//If elevator is either at top or bottom floor, it will request to stop
	if (current_floor == 3 || current_floor == 0)
	{
		return 0;
	}
	for (int button = 0; button < N_BUTTONS; button++)
	{
		if (dir == 0)
		{
			for (int floor_above = current_floor + 1; floor_above < N_FLOORS; floor_above++)
			{
				if (get_order(floor_above, button))
				{
					return 1;
				}
			}
		}

		else if (dir == 1)
		{
			for (int floor_below = current_floor -1; floor_below >= 0; floor_below--;)
			{
				if (get_order(floor_below, button))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}