
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "state.h"
#include "door.h"

state_t* state;
// door_t door_1;
// door_t door_2;

void _INIT ProgramInit(void)
{
	// set all output to zero
	door_1.motor_opening = FALSE;
	door_1.motor_closing = FALSE;
	door_1.display = FALSE;
	
	door_2.motor_opening = FALSE;
	door_2.motor_closing = FALSE;
	door_2.display = FALSE;
	
	// check for correct door position
	if (door_1.sensor_closed && door_2.sensor_closed)
	{
		// set state to DOORS_CLOSED
		state = &state_doors_closed;
	}
	else
	{
		state = &state_error;
	}
}
