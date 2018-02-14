#include <stdlib.c>
#include <time.h>

#include "orders.h"
#include "prioritizer.h"
#include "assorted_funcs.c"
#include "elev.c"
#include "io.c"
#include "channels.h"

int main(){
	
	int current_floor;
	int current_dir;
	int current_state;

	int requested_floor;

	int stop = 0;
	int stop_button = 0;

	initialize_lift(void);

	current_floor = enter_defined_state();
	elev_set_floor_indicator(current_floor);

	current_dir = 0; // 0 = Up, 1 = Down

	//
	while (1) // Standby
	{
		receive_orders();
		requested_floor = pending_orders();
		if(requested_floor)
		{
			move_to_floor(current_floor, requested_floor);
			while (1) //Moving
			{
				receive_orders();
				current_state = elev_get_floor_sensor_signal();
				stop_button = elev_get_stop_signal();
				current_dir = elev_get_motor_direction()

				if (stop_button)
				{
					elev_set_motor_direction(DIRN_STOP);
					elev_set_stop_lamp(1);
					clear_all_orders();
					if (elev_get_floor_sensor_signal() != -1)
					{
						elev_set_door_open_lamp(1);
					}
					while (elev_get_stop_signal()){continue;}
					elev_set_door_open_lamp(0);
					elev_set_stop_lamp(0);
					stop_button = 0;
					break;
				}
				else if ((current_state == N_FLOORS - 1)||(current_state == 0))
				{
					stop = 1;
				}
				else if ((current_state != current_floor)&&(current_state != -1))
				{
					stop = prioritized_floor(current_state, current_dir);
				}

				if (stop)
				{
					elev_set_motor_direction(DIRN_STOP);
					clear_order(current_floor);
					set_door_open_for_n_seconds(3);
					break;
				}
			}
			current_floor = current_state;
		}

	}

	return 0;
}