#include <stdlib.h>
#include <stdio.h>
#include "elev.h"
#include "fsm.h"

int main(){

	int stop_button;
	int door_open;

	int current_floor;
	int current_dir;

	while(1){
		stop_button = elev_get_stop_signal();
		door_open = elev_get_door_open_lamp();
		current_floor = elev_get_floor_sensor_signal();
		current_dir = elev_get_motor_direction();
		fsm(stop_button, current_floor, door_open, current_dir);
	}

	return 0;
}