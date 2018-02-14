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
		elev_set_motor_direction(DIRN_STOP);
	}
	

}

int floor_order(int floor, int dir){

	//Returns 1 if ether COMMAND button or order in suggested direction is active
	if(elev_get_button_lamp(floor, 2) || elev_get_button_lamp(floor, dir)){
		printf("FLOOR_ORDER Returnerer 1\n");
		return 1;
	}
		
	printf("FLOOR_ORDER Returnerer 0\n");
	return 0;

}


int orders_ahead(int reached_floor, int dir){
	//If elevator is either at top or bottom floor, it will request to stop
	if(reached_floor == 3 || reached_floor == 0){
		return 0;
	}

	//If direction is UP, elevator checks lights in floors above. 
	else if(dir == 0){
		for(int above = reached_floor+1; above <= N_FLOORS; above = above +1){
			for (int lamp = 0; lamp < N_BUTTONS ; lamp += 1){
				if(elev_get_button_lamp(above, lamp)){
					printf("orders_ahead FANT ETASJER OVER!\n");
					return 1;
				}
			}
		}
	}

	////If direction is DOWN, elevator checks lights in floors below.
	else if(dir == 1){
		for(int below = reached_floor-1; below <= 0; below = below -1){
			for (int lamp = 0; lamp < N_BUTTONS ; lamp += 1){
				if(elev_get_button_lamp(below, lamp)){
					printf("orders_ahead FANT ETASJER under!\n");
					return 1;
				}
			}
		}
	}
	printf("orders_ahead FANT INGEN ETASJER!\n");
	return 0;


}


int prioritized_floor(int reached_floor, int dir){
 	printf("KJØRER PRIORITERINGSALGORITME\nDIR: ");
 	printf("%d", dir);
 	printf("\n\n");


	//Buttons and motor operate with different dir indexing. Scaling dir from motor to buttons for further use

	//The function suggested_stop returns 2 if the lift has an active order made inside itself,
	//0 if it has an active order from reached floor in UP dir
	//1 if there is and active order from reached floor in DOWN dir
	//-1 elsewise


	if(floor_order(reached_floor, dir)){
		printf("floor_order(dir) STOPP!\n\n");
		return 1;

	}
	//else{printf("FLOOR_ORDER FEILER");}


	if (floor_order(reached_floor, !dir) && (!(orders_ahead(reached_floor, dir)))){
		printf("floor_order(!dir) STOPP! \n\n");
		return 1;
	}

	
	
	return 0;

}


void receive_orders(void){

	int suspicious_floor = any_button();
	

	if(suspicious_floor != -1){
		suspicious_floor = suspicious_floor -1;
		

		for(int i = 0; i<N_BUTTONS; i = i+1){
			if(!((suspicious_floor==0 && i == 1)||(suspicious_floor==3 && i ==0))){
				if(elev_get_button_signal(i, suspicious_floor)){
					elev_set_button_lamp(i, suspicious_floor, 1);
					break;
					
				}
			}
		}


	}
}

void clear_lamps(int floor){

	for(int i = 0; i<N_BUTTONS; i = i+1){
			if(!((floor==0 && i == 1)||(floor==3 && i ==0))){
				elev_set_button_lamp(i, floor, 0);
										
				
			}
	}


}