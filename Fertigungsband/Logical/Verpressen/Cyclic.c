
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	// TODO Error Handling
	
	switch (Status)
	{
		case INIT:
			if (Zylinder_oben)
			{
				Zylinder_auf = 0;
				Status = BEREIT;
			}
			break;
		
		case BEREIT:
			if (Teil_vorhanden)
			{
				Lampe_Q2 = 1;
				Zylinder_ab = 1;
				Status = ZYLINDER_AB;
			}
			break;
		
		case ZYLINDER_AB:
			if (Zylinder_unten)
			{
				Zylinder_ab = 0;
				Zylinder_auf = 1;
				Status = ZYLINDER_AUF;
			}
			break;
		
		case ZYLINDER_AUF:
			if (Zylinder_oben)
			{
				Zylinder_auf = 0;
				Lampe_Q2 = 0;
				Status = FERTIG;
			}
			break;
		
		case FERTIG:
			if (!Teil_vorhanden)
			{
				Status = BEREIT;
			}
			break;
		
		case FEHLER:
			// TODO
			Zylinder_auf = 0;
			Zylinder_ab = 0;
			Lampe_Q1 = 1;
			Lampe_Q2 = 0;
			break;
		
		default:
			Status = FEHLER;
			break;
	}
}
