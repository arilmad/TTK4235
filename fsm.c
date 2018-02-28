
static const STATE PREVIOUS_STATE;
static const STATE CURRENT_STATE;

void fsm_init(void){
	PREVIOUS_STATE = STANDBY;
	CURRENT_STATE = STANDBY;
}


STATE fsm_get_state(void){
	return CURRENT_STATE;
}

void fsm_set_new_state(STATE NEW_STATE){
	CURRENT_STATE = NEW_STATE;
}




void fsm_state_machine(){


	switch(CURRENT_STATE){

	case STANDBY:

	if(anyButton + 1){

		int requested_floor = pending_orders() + 1;

		CURRENT_STATE = RUNNING;
	}



	}

}