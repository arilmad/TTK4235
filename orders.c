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

void receive_orders(void)
{
	for (int floor = 0; floor < N_FLOORS; floor++)
	{
		for (int button = 0; button < N_BUTTONS; button++)
		{
			if ((floor == (N_FLOORS - 1)) && (button == 0))
			{
				continue;
			}
			else if ((floor == 0) && (button == 1))
			{
				continue;
			}
			else
			{
				orders[floor][button] = elev_get_button_signal(button, floor);
				if(orders[floor][button])
				{
					elev_set_button_lamp(button, floor, 1);
				}
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
	return -1;
}

void clear_order(int floor)
{
	for (int button = 0; button < N_BUTTONS; button++)
	{
		//printf("clear_order kjører \n");
		if ((floor == (N_FLOORS - 1)) && (button == 0))
		{
			continue;
		}
		else if ((floor == 0) && (button == 1))
		{
			continue;
		}
		else
		{
			orders[floor][button] = 0;
			elev_set_button_lamp(button, floor, orders[floor][button]);
		}
	}
}

void clear_all_orders(void)
{
	for (int floor = 0; floor < N_FLOORS; floor++)
	{
		printf("clear_all_orders kjører \n");
		clear_order(floor);
	}
}