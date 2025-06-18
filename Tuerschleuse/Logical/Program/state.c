#include "state.h"
#include "door.h"
#include <stddef.h>

static state_t* state_func_doors_closed();
static state_t* state_func_door_1_opening();
static state_t* state_func_door_2_opening();
static state_t* state_func_door_1_open();
static state_t* state_func_door_2_open();
static state_t* state_func_door_1_closing();
static state_t* state_func_door_2_closing();
static state_t* state_func_error();

state_t state_doors_closed = 	{"Doors closed", state_func_doors_closed};
state_t state_door_1_opening = 	{"Door 1 opening", state_func_door_1_opening};
state_t state_door_2_opening = 	{"Door 2 opening", state_func_door_2_opening};
state_t state_door_1_open = 	{"Door 1 open", state_func_door_1_open};
state_t state_door_2_open = 	{"Door 2 open", state_func_door_2_open};
state_t state_door_1_closing = 	{"Door 1 closing", state_func_door_1_closing};
state_t state_door_2_closing = 	{"Door 2 closing", state_func_door_2_closing};
state_t state_error = 			{"Error", state_func_error};

// extern door_t door_1;
// extern door_t door_2;

state_t* state_func_doors_closed()
{
	if (door_1.button_outside || door_1.button_inside)
	{
		//door_1.timer = set_TON(door_1.timer, FALSE, DOOR_OPEN_TIMEOUT);
		door_1.timer = reset_TON(door_1.timer);
		return &state_door_1_opening;
	}
	else if (door_2.button_outside || door_2.button_inside)
	{
		//door_2.timer = set_TON(door_2.timer, FALSE, DOOR_OPEN_TIMEOUT);
		door_2.timer = reset_TON(door_2.timer);
		return &state_door_2_opening;
	}
	
	return &state_doors_closed;
}

state_t* state_func_door_1_opening()
{
	if (!door_1.motor_opening) door_1.motor_opening = TRUE;
	
	door_1.timer = set_TON(door_1.timer, TRUE, DOOR_OPENING_ERROR);
	
	if (door_1.sensor_opened)
	{
		door_1.motor_opening = FALSE;
		// Fix? reset timer
		// door_1.timer = set_TON(door_1.timer, FALSE, DOOR_OPEN_TIMEOUT);
		door_1.timer = reset_TON(door_1.timer);
		return &state_door_1_open;
	}
	
	if (door_1.timer.Q)
	{
		return &state_error;
	}
	
	return &state_door_1_opening;
}

state_t* state_func_door_1_open()
{
	door_1.timer = set_TON(door_1.timer, TRUE, DOOR_OPEN_ERROR);
	if (door_1.timer.ET > DOOR_OPEN_TIMEOUT && door_1.sensor_barrier)
	{
		//door_1.timer = set_TON(door_1.timer, FALSE, DOOR_OPEN_TIMEOUT); // reset timer
		door_1.timer = reset_TON(door_1.timer);
		return &state_door_1_closing;
	}

	if (door_1.timer.Q)
	{
		return &state_error;
	}
	
	return &state_door_1_open;
}

state_t* state_func_door_1_closing()
{
	if (!door_1.motor_closing) door_1.motor_closing = TRUE;
	
	door_1.timer = set_TON(door_1.timer, TRUE, DOOR_CLOSING_ERROR);
	
	door_display(&door_1, BLINK_SLOW);
	
	if (!door_1.sensor_barrier || door_1.button_outside || door_1.button_inside)
	{
		door_1.motor_closing = FALSE;
		door_1.display = FALSE;
		door_1.timer = reset_TON(door_1.timer);
		return &state_door_1_opening;
	}
	else if (door_1.sensor_closed)
	{
		door_1.motor_closing = FALSE;
		door_1.display = FALSE;
		return &state_doors_closed;
	}
	
	if (door_1.timer.Q)
	{
		return &state_error;
	}
	
	return &state_door_1_closing;
}

state_t* state_func_door_2_opening()
{
	if (!door_2.motor_opening) door_2.motor_opening = TRUE;
	
	door_2.timer = set_TON(door_2.timer, TRUE, DOOR_OPENING_ERROR);
	
	if (door_2.sensor_opened)
	{
		door_2.motor_opening = FALSE;
		// Fix? reset timer
		//door_2.timer = set_TON(door_2.timer, FALSE, DOOR_OPEN_TIMEOUT);
		door_2.timer = reset_TON(door_2.timer);
		return &state_door_2_open;
	}
	
	if (door_2.timer.Q)
	{
		return &state_error;
	}
	
	return &state_door_2_opening;
}

state_t* state_func_door_2_open()
{
	door_2.timer = set_TON(door_2.timer, TRUE, DOOR_OPEN_ERROR);
	
	if (door_2.timer.ET > DOOR_OPEN_TIMEOUT && door_2.sensor_barrier)
	{
		//door_2.timer = set_TON(door_2.timer, FALSE, DOOR_OPEN_TIMEOUT); // reset timer
		door_2.timer = reset_TON(door_2.timer);
		return &state_door_2_closing;
	}
	
	if (door_2.timer.Q)
	{
		return &state_error;
	}
	
	return &state_door_2_open;
}

state_t* state_func_door_2_closing()
{
	if (!door_2.motor_closing) door_2.motor_closing = TRUE;
	
	door_2.timer = set_TON(door_2.timer, TRUE, DOOR_CLOSING_ERROR);
	
	door_display(&door_2, BLINK_SLOW);
	
	if (!door_2.sensor_barrier || door_2.button_outside || door_2.button_inside)
	{
		door_2.motor_closing = FALSE;
		door_2.display = FALSE;
		door_2.timer = reset_TON(door_2.timer);
		return &state_door_2_opening;
	}
	else if (door_2.sensor_closed)
	{
		door_2.motor_closing = FALSE;
		door_2.display = FALSE;
		return &state_doors_closed;
	}
	// TODO: error handling
	
	if (door_2.timer.Q)
	{
		return &state_error;
	}
	
	return &state_door_2_closing;
}

state_t* state_func_error()
{
	door_1.motor_opening = FALSE;
	door_1.motor_closing = FALSE;
	door_2.motor_opening = FALSE;
	door_2.motor_closing = FALSE;
	
	door_display(&door_1, BLINK_FAST);
	door_display(&door_2, BLINK_FAST);
	
	door_1.timer = set_TON(door_1.timer, door_1.button_outside, DOOR_RESET_TIMEOUT);
	door_2.timer = set_TON(door_2.timer, door_2.button_outside, DOOR_RESET_TIMEOUT);
	
	if (door_1.timer.Q || door_2.timer.Q)
	{
		door_1.display = FALSE;
		door_2.display = FALSE;
		
		if (door_1.sensor_closed && door_2.sensor_closed)
		{
			return &state_doors_closed;
		}
		if (!door_1.sensor_closed && door_2.sensor_closed)
		{
			return &state_door_1_closing;
		}
		if (door_1.sensor_closed && !door_2.sensor_closed)
		{
			return &state_door_2_closing;
		}
	}
	
	return &state_error;
}
