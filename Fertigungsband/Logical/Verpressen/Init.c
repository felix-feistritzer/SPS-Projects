
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	Lampe_Q2 = 0;
	
	if (Zylinder_oben)
	{
		Zylinder_auf = 0;
		Zylinder_ab = 0;
		Status = BEREIT;
	}
	else
	{
		Zylinder_auf = 1;
		Zylinder_ab = 0;
		Status = INIT;
	}
}
