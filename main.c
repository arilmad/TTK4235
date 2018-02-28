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
	int prev_floor;

	initialize_lift();

	int stop_button;
	int requested_floor;
	int is_door_open;
	int new_order;
	int current_floor;
	while(1){


		//mottar ordre og setter lamper. Returnerer 1 hvis ny ordre plukkes opp
		new_order = receive_orders();
		stop_button = elev_get_stop_signal();	
		
		is_door_open = elev_get_door_open_lamp;
		current_floor = elev_get_floor_sensor_signal;

		if(current_floor != -1){

			fsm_update_state_machine(current_floor);
		}

		else if(stop_button){
			
		}

	}
	return 0;
}