#include "orders.h"

static int orders[N_FLOORS][N_BUTTONS] = 
{
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
};
 
int get_order(int floor, int button)
{
	return orders[floor][button];
}

void recieve_orders(void)
{
	for (int floor = 0; floor < N_FLOORS; floor++)
	{
		for (int button = 0; button < N_BUTTONS; button++)
		{
			if ((floor == N_FLOORS) - 1 && (button == 0))
			{
				continue;
			}
			else if ((floor == 0) - 1 && (button == 1))
			{
				continue;
			}
			else
			{
				orders[floor][button] = elev_get_button_signal(button, floor);
				elev_set_button_lamp(button, floor, orders[floor][button]);
			}
		}
	}
}

int pending_orders(void)
{
	for (int floor = 0; floor < N_FLOORS; floor++)
	{
		for (int button = 0; button < N_BUTTONS; button++)
		{
			if (orders[floor][button] == 1)
			{
				return floor;
			}
		}
	}
	return 0;
}

void clear_order(int floor)
{
	for (int button = 0; button < N_BUTTONS; button++)
	{
		orders[floor][button] = 0;
		elev_set_button_lamp(button, floor, orders[floor][button]);
	}
}

void clear_all_orders(void)
{
	for (int floor = 0; floor < N_FLOORS; floor++)
	{
		clear_order(floor);
	}
}