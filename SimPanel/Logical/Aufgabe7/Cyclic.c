
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define DI3 	0
#define DELAY	500	// ms

TON_typ set_TON(TON_typ TONset, BOOL IN);

void _CYCLIC ProgramCyclic(void)
{
	if (Sw1)
	{
		LED1 = 1;
		
		BtnTOn[DI3].IN = 1;
		
		if (BtnTOn[DI3].Q)
		{
			BtnArray[DI3].LEDR = !BtnArray[DI3].LEDR;
			BtnTOn[DI3].IN = 0;
		}
		
		BtnTOn[DI3] = set_TON(BtnTOn[DI3], BtnTOn[DI3].IN);
	}
	else
	{
		LED1 = 0;
		BtnArray[DI3].LEDR = 0;
	}
}

TON_typ set_TON(TON_typ TONset, BOOL IN)
{
	TONset.IN = IN;
	TONset.PT = DELAY;
	TON(&TONset);
	return TONset;
}