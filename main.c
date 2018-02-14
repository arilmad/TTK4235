#include "assorted_funcs.h"
#include "channels.h"
#include "io.h"
#include "elev.h"
#include <stdlib.h>
#include <comedilib.h>
#include <time.h>

int main(){

	
	initialize_lift();

	//Makes sure the lift is at defined state and sets floor indicator lamp.
	int current_floor = enter_defined_state();
	elev_set_floor_indicator(current_floor);

	//initial DIR D/C
	int prev_dir = 0;


	while(1){


		//Initial condition. Lift is at this stage not summoned by any floor.
		//floor_summ is the floor to which the lift is summoned, -1 indicates no buttons are pressed
		receive_orders();


		if(VI HAR AKTIVE BESTILLINGER){


			printf("REGISTERED DIR: ");
			printf("%d", prev_dir);
			printf("\n\n");

			receive_orders();

			//Securing 0 indexing of floors for further operations
				
			

			if(orders_ahead(current_floor, dir)){
				while(DØR){continue;}
				KJØR
			}

			else if(orders_ahead(current_floor, !dir)){
				while(DØR){continue;}
				dir = !dir


				KJØR

			}

			//Lift refuses to move before the door is confirmed closed
			//while(!elev_get_door_open_lamp()){continue;}


			//Lift approaches destination and calculates in which direction to move
			//move_to_floor(current_floor, floor_summ);



			//Lift continues to move until a prioritized floor has been reached
			while(1){
				receive_orders();


				//Sets floor indicator as we go
				//KAN PUTTES ET ANNET STED

				int current_state = elev_get_floor_sensor_signal();
				if ((current_state != current_floor)&&(current_state != -1)){
					elev_set_floor_indicator(current_state);
					current_floor = current_state;
					int stop_now = prioritized_floor(current_state, elev_get_motor_direction());
					if(stop_now){
						prev_dir = elev_get_motor_direction();
						elev_set_motor_direction(DIRN_STOP);
					break;
				}
				
				

				}
				else{continue;}
			}
			


			current_floor = elev_get_floor_sensor_signal();
			clear_lamps(current_floor);
			set_door_open_for_n_seconds(3);
					
				//floor_summ = -1;
			



		}
			

		


		//if(onetime){break;}
	}

	


	return 0;

}











