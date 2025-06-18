#pragma once

#define DOOR_OPEN_TIMEOUT 		 5000 //  5 sec
#define DOOR_RESET_TIMEOUT		 3000 //  3 sec
#define DOOR_OPENING_ERROR		10000 // 10 sec
#define DOOR_OPEN_ERROR			20000 // 20 sec
#define DOOR_CLOSING_ERROR		10000 // 10 sec

typedef struct state* (*state_func_t)();
typedef struct state
{
	const char* name;
	state_func_t run;
} state_t;

extern state_t state_doors_closed;
extern state_t state_door_1_opening;
extern state_t state_door_2_opening;
extern state_t state_door_1_open;
extern state_t state_door_2_open;
extern state_t state_door_1_closing;
extern state_t state_door_2_closing;
extern state_t state_error;
