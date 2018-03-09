#ifndef __FSM_H__
#define __FSM_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "order_handling.h"
#include "prioritizer.h"
#include "timer.h"
#include "elev.h"

#define DOOR_OPEN_N_SECONDS 3

typedef enum state {
	INIT = -1,
	MOVING = 0,
	STANDBY = 1,
	STOP_BUTTON = 2,
	DOOR_OPEN = 3,
} state_t;

void fsm ();

#endif