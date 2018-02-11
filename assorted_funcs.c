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

int floor_order(int floor){

	//COMMANDs are most prioritized. Iterating through lamps in prioritized order
	for(int i = 2; i >-1; i = i-1){
		if(elev_get_button_lamp(floor, i)){
			return i;
		}
	}
	return -1;

}


int ordersAhead(int reached_floor, int dir){

	//If elevator is either at top or bottom floor, it will request to stop
	if(reached_floor == 3 || reached_floor == 0){
		return 0;
	}

	//If direction is UP, elevator checks lights in floors above. 
	else if(dir == 0){
		for(int above = reached_floor; above <= N_FLOORS; above = above +1){
			if((floor_order(above))!= -1){
				return 1;
			}
		}
	}

	////If direction is DOWN, elevator checks lights in floors below.
	else if(dir == 1){
		for(int below = reached_floor; below <= 0; below = below -1){
			if((floor_order(below))!= -1){
				return 1;
			}
		}
	}
	return 0;


}


int prioritized_floor(int reached_floor, int dir){


	//Buttons and motor operate with different dir indexing. Scaling dir from motor to buttons for further use
	if(dir == -1){dir =1;}
	else if(dir == 1){dir = 0;}

	//The function suggested_stop returns 2 if the lift has an active order made inside itself,
	//0 if it has an active order from reached floor in UP dir
	//1 if there is and active order from reached floor in DOWN dir
	//-1 elsewise

	int amIWanted = floor_order(reached_floor);

	//Lift will prioritize stop either if someone inside the lift has ordered the floor 
	//or if someone has summoned the lift and the lift is currently moving in the desired direction
	if(amIWanted==1 || amIWanted ==2){
		return 1;
	}

	//If there is an active order from this floor in the opposite direction, the lift will check if there are orders from floors ahead and prioritize stop if not.
	else if((amIWanted ==2) && (!(ordersAhead(reached_floor, dir)))){
		return 1;
	}

	return 0;

}


void receive_orders(void){

	int suspicious_floor = any_button();
	

	if(suspicious_floor != -1){
		suspicious_floor = suspicious_floor -1;
		printf("SUSP FLOOR: ");
		printf("%d", suspicious_floor);

		for(int i = 0; i<N_BUTTONS; i = i+1){
			if(!(suspicious_floor==0 && i == 1)||(suspicious_floor==3 && i ==0)){
				if(elev_get_button_signal(i, suspicious_floor)){
					elev_set_button_lamp(i, suspicious_floor, 1);
					break;
					
				}
			}
		}


	}
}