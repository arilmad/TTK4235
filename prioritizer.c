#include "prioritizer.h"

int prioritized_floor(int current_floor, int dir)
{
	//Buttons and motor operate with different dir indexing. Scaling dir from motor to buttons for further use

	//The function suggested_stop returns 2 if the lift has an active order made inside itself,
	//0 if it has an active order from reached floor in UP dir
	//1 if there is and active order from reached floor in DOWN dir
	//-1 elsewise
	int command = get_order(current_floor, 2);
	int dir_button = get_order(current_floor, dir);
	int orders = orders_ahead(current_floor, dir);
	printf("Direction: ");
	printf("%d\n", dir);
	printf("Command button: ");
	printf("%d\n", command);
	printf("Dir button: ");
	printf("%d\n", dir_button);
	printf("Orders ahead: ");
	printf("%d\n", orders);


	int ordered_at_current_floor = (get_order(current_floor, 2) || get_order(current_floor, dir));

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

int orders_ahead(int reached_floor, int dir){

	//If elevator is either at top or bottom floor, it will request to stop
	if(reached_floor == 3 || reached_floor == 0)
	{
		return 0;
	}

	//If direction is UP, elevator checks lights in floors above. 
	else if (dir == 0)
	{
		for (int above = reached_floor+1; above < N_FLOORS; above++)
		{
			for (int button = 0; button < N_BUTTONS ; button++)
			{
				if (get_order(above, button))
				{
					return 1;
				}
			}
		}
	}

	////If direction is DOWN, elevator checks lights in floors below.
	else if (dir == 1){
		for (int below = reached_floor-1; below > -1; below--)
		{
			for (int button = 0; button < N_BUTTONS ; button++)
			{
				if (get_order(below, button))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}