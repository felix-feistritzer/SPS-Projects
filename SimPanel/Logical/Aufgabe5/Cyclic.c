
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	if (Sw1)
	{
		LED1 = 1;
		DISP = P1 / 327; // Values Range [0, 32767] => [0, 100]
	}
	else
	{
		LED1 = 0;
		DISP = 0;
	}
}
