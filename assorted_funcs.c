#include "assorted_funcs.h"


int initialize_lift(void)
{
	
	elev_init();

	int floor = elev_get_floor_sensor_signal();

	if (floor != -1)
	{
		return floor;
	}

	elev_set_motor_direction(DIRN_UP); //Assumes we are below 4. floor.

	while(floor == -1)
	{
		floor = elev_get_floor_sensor_signal();
	}

	elev_set_motor_direction(DIRN_STOP);
	elev_set_floor_indicator(floor);
	return floor;

}

void move_to_floor(double current_floor, int desired_floor)
{
	if (current_floor < (double)desired_floor)
	{
		elev_set_motor_direction(DIRN_UP);
	}

	else if (current_floor > (double)desired_floor)
	{
		elev_set_motor_direction(DIRN_DOWN);
	}

	else
	{
		elev_set_motor_direction(DIRN_STOP);
	}

}

int timer(int count_s, clock_t reference)
{
	clock_t new_time = clock();

	if (((new_time - reference)/CLOCKS_PER_SEC) >= count_s)
	{
		return 1;
	}
	return 0;
}