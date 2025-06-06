#pragma once

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#define FALSE 0
#define TRUE  1
#define BLINK_SLOW	600
#define BLINK_FAST	200

/*
typedef struct door
{
	// inputs
	BOOL button_outside;
	BOOL button_inside;
	BOOL sensor_closed;
	BOOL sensor_opened;
	BOOL sensor_barrier;
	
	// outputs
	BOOL motor_opening;
	BOOL motor_closing;
	BOOL display;
	
	// intern
	TON_typ timer;
} door_t;
*/

void door_display(door_t* self, TIME blink_speed);
TON_typ set_TON(TON_typ TONset, BOOL in, TIME delay);
