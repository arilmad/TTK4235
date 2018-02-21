#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "orders.h"
#include "prioritizer.h"
#include "assorted_funcs.h"
#include "elev.h"
#include "io.h"
#include "channels.h"

int main(){
	
	int current_floor;
	int current_dir;
	int current_state;
	int prev_floor = -1;

	int requested_floor;
	int prev_dir = -1;
	int stop = 0;
	int stop_button = 0;


	//current_floor er 0-initialisert
	current_floor = initialize_lift();
	printf("Current floor: ");
	printf("%d\n", current_floor);


	elev_set_floor_indicator(current_floor);
	current_dir = 0; // 0 = Up, 1 = Down

	set_door_open_for_n_seconds(3);

	
	//
	while (1) // Standby
	{
		
		//receive_orders itererer gjennom alle knapper og setter lamper
		receive_orders();

		//requested_floor returnerer første etasje FRA BUNNEN som har aktiv bestilling. Returnerer -1 hvis ingen bestilling.
		requested_floor = pending_orders() + 1;
		stop_button = elev_get_stop_signal();

		if (requested_floor != 0 || stop_button)
		{
			requested_floor -= 1;
			move_to_floor(current_floor, requested_floor);
			
			if(elev_get_floor_sensor_signal() == -1)
			{
				if(requested_floor == current_floor)
				{
					if(current_dir == 1)
					{
						elev_set_motor_direction(DIRN_UP);
					}
					else if(current_dir == 0)
					{
						elev_set_motor_direction(DIRN_DOWN);
					}
				}
				//current_dir = elev_get_motor_direction();
			}
			while (1) //Moving
			{
				receive_orders();
				current_state = elev_get_floor_sensor_signal();
				stop_button = elev_get_stop_signal();
				current_dir = elev_get_motor_direction();

				if (stop_button)
				{
					elev_set_motor_direction(DIRN_STOP);
					elev_set_stop_lamp(1);
					clear_all_orders();

					while (elev_get_stop_signal()){continue;}
					elev_set_stop_lamp(0);
					stop_button = 0;

					if (elev_get_floor_sensor_signal() != -1)
					{
						//clock_t reference_time = clock();
						//elev_set_door_open_lamp(1);
						//while(!(timer(3, reference_time))){continue;}
						set_door_open_for_n_seconds(3);
						//elev_set_door_open_lamp(0);
					}
					//prev_dir = current_dir;
					break;
				}

				else if ((current_state != current_floor) && (current_state != -1))
				{
					prev_floor = current_state;
					elev_set_floor_indicator(current_state);
					stop = prioritized_floor(current_state, current_dir);
				}

				else if ((current_state == current_floor) && (get_order_from_floor(current_floor)))
				{
					stop = 1;
					while(button_held_down_in_floor(current_floor)){continue;}

				}

				if (stop)
				{
					elev_set_motor_direction(DIRN_STOP);
					prev_floor = current_state;
					current_floor = current_state;

					clear_order(current_floor);
					printf("Clearing all orders in floor ");
					printf("%d", current_floor );
					printf("\n");
					printf("%d", get_order_from_floor(current_floor));
					printf("\n");
					stop = 0;


					while(1)
					{
						set_door_open_for_n_seconds(3);

						if(get_order_from_floor(current_floor))
						{

							clear_order(current_floor);
							
							continue;
						}
						break;
					}

					if(!(pending_orders()+1))
					{
						printf("pending_orders finner ingen pending orders\n");

						break;
					}
					if(pending_orders()+1)
					{
						printf("pending_orders finner pending orders\n");
					}

					requested_floor = orders_ahead(current_floor, current_dir)+1;
					
					if(requested_floor)

					{
						printf("Move to floor i samme dir\n");
						if (current_dir == 0) {
							elev_set_motor_direction(DIRN_UP);
						}
						else if (current_dir == 1)
						{
							elev_set_motor_direction(DIRN_DOWN);
						}
					}

					else
					{
						printf("Move to floor i motsatt dir\n");
						if (current_dir == 1) {
							elev_set_motor_direction(DIRN_UP);
						}
						else if (current_dir == 0)
						{
							elev_set_motor_direction(DIRN_DOWN);
						}

					}

				}
			}
		}

	}

	return 0;
}