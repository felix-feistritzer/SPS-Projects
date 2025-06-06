
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "state.h"
#include "door.h"
#include <stddef.h>

extern state_t* state;

void _CYCLIC ProgramCyclic(void)
{
	if (state != NULL)
	{
		state = state->run();
	}
	// TODO: error handling
}

