#include "assorted_funcs.h"
#include "elev.h"
#include "io.h"
#include <comedilib.h>
#include <stdlib.h>
#include <stdio.h>




void initialize_lift(void){

	io_init();
	elev_init();
}



int enter_defined_state(void){

	if (elev_get_floor_sensor_signal() != -1){
		return elev_get_floor_sensor_signal();
	}

	//Setter pådrag utenfor while-løkka, og genererer med det noen ekstra linjer kode.

	elev_set_motor_direction(DIRN_UP); //Forutsetter at vi aldri befinner oss over 4. etasje.

	while(elev_get_floor_sensor_signal() == -1){continue;}

	elev_set_motor_direction(DIRN_STOP);

	return elev_get_floor_sensor_signal();
}



int any_button(void){
	
	for(int floor = 0; floor < N_FLOORS; floor = floor +1) {

		for(int button = 0; button < N_BUTTONS; button = button +1){

			//Det er ikke lov å trykke nedover når man er i 1. etg eller oppover når man er i 4.
			if(!((floor == 0 && button == 1) || (floor == 3 && button == 0))){

				//Returner hvilken etasje heisen kalles fra. 
				if(elev_get_button_signal(button, floor)) {
					


					//Feilsøking. Funksjonen funker som den skal.
					printf("FLOOR RETURNED: ");
					printf("%d", floor+1);					
					printf("\n");


					//O-indeksering førte til at løkke i main ikke virket. 
					return floor+1;
				}
			}

		}

		
	}
	//Returner -1 hvis ingen kaller på heisen
	return -1;


}

void move_to_floor(int current_floor, int desired_floor){
	printf("MOVETOFLOOR ACTIVATED\n");
	if(current_floor < desired_floor){
		elev_set_motor_direction(DIRN_UP);
	}

	else if(current_floor > desired_floor){
		elev_set_motor_direction(DIRN_DOWN);
	}

	else{
		elev_set_motor_direction(DIRN_UP);
	}
	

}