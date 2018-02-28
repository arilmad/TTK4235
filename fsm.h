#ifndef __FSM_H__
#define __FSM_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "orders.h"
#include "prioritizer.h"
#include "assorted_funcs.h"
#include "elev.h"

typedef enum state {
	INIT = -1,
	MOVING = 0,
	STANDBY = 1,
	STOP_BUTTON = 2,
	DOOR_OPEN = 3,
} state_t;

void fsm (int stop_button, int current_floor, int door_open, int current_dir);

#endif