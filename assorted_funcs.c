#include "assorted_funcs.h"
#include "elev.h"

void enter_defined_state(void){

	if elev_get_floor_sensor_signal() != -1 {
		return;
	}

	//Setter pådrag utenfor while-løkka, og genererer med det noen ekstra linjer kode.

	elev_set_motor_direction(elev_motor_direction_t DIRN_UP); //Forutsetter at vi aldri befinner oss over 4. etasje.

	while(elev_get_floor_sensor_signal() == -1){continue;}

	elev_set_motor_direction(elev_motor_direction_t DIRN_STOP);

	return;