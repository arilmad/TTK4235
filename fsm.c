

static const STATE CURRENT_STATE;




STATE get_state(void){
	return CURRENT_STATE;
}

void set_state(STATE NEW_STATE){
	CURRENT_STATE = NEW_STATE;
}




void state_machine(){

	switch(CURRENT_STATE){

	case STANDBY:

	if(anyButton + 1){

		

		CURRENT_STATE = RUNNING;
	}



	}

}