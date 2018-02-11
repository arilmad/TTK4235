#include "assorted_funcs.h"
#include "channels.h"
#include "io.h"
#include "elev.h"
#include <stdlib.h>
#include <comedilib.h>

int main(){

	
	initialize_lift();

	//Makes sure the lift is at defined state and sets floor indicator lamp.
	int current_floor = enter_defined_state();
	elev_set_floor_indicator(current_floor);
	int onetime = 0;

	while(1){

		
		//Initial condition. Lift is at this stage not summoned by any floor.
		//elev_motor_direction_t current_dir = DIRN_STOP;

		//floor_summ is now the floor to which the lift is summoned, -1 indicates no buttons are pressed

		int floor_summ = any_button();
		
		

		if(floor_summ != -1){

			floor_summ = floor_summ -1;
			
			printf("ANYBUTTON ");
			printf("%d", floor_summ);
			//Lift refuses to move before the door is confirmed closed
			while(!elev_get_door_open_lamp()){continue;}
			
			//printf("NEXT LEVEL SHIT");
			move_to_floor(current_floor, floor_summ);

			while(elev_get_floor_sensor_signal() != floor_summ){continue;}
			onetime = 1;

			elev_set_motor_direction(DIRN_STOP);

			current_floor = elev_get_floor_sensor_signal();
			
			//floor_summ = -1;



		}
			

		


		//if(onetime){break;}
	}

	


	return 0;

}











