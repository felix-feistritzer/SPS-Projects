
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#include "door.h"

// extern door_t door_1;
// extern door_t door_2;

void _EXIT ProgramExit(void)
{
	// set all output to zero
	door_1.motor_opening = FALSE;
	door_1.motor_closing = FALSE;
	door_1.display = FALSE;
	
	door_2.motor_opening = FALSE;
	door_2.motor_closing = FALSE;
	door_2.display = FALSE;
}
