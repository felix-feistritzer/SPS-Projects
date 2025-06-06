
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define BTN_NUMBER 4

R_TRIG_typ set_R_TRIG(R_TRIG_typ Rset, BOOL CLK);
TON_typ set_TON(TON_typ Tset, BOOL IN);

void toggleLED(int index);

void _CYCLIC ProgramCyclic(void)
{
	int cnt;
	
	// Dedect Rising Edge of Switch 1
	Sw1_Rise = set_R_TRIG(Sw1_Rise, Sw1);
	
	// Dedect Delay and Rising Edge Button 3-6
	for (cnt = 0; cnt < BTN_NUMBER; cnt++)
	{
		BtnTOn[cnt] = set_TON(BtnTOn[cnt], BtnArray[cnt].Btn);
		BtnArray[cnt].Btn_Rise = set_R_TRIG(BtnArray[cnt].Btn_Rise, BtnTOn[cnt].Q);
	}
	
	// Check if any Button Rise is true
	for (cnt = 0; cnt < BTN_NUMBER; cnt++)
	{
		if (Sw1 && BtnArray[cnt].Btn_Rise.Q)
		{
			toggleLED(cnt);
		}
	}
	
	// Switch 1 turned on -> all red LEDs on
	if (Sw1_Rise.Q)
	{
		for(cnt = 0; cnt < BTN_NUMBER; cnt++)
		{
			BtnArray[cnt].LEDR = 1;
		}
	}
	
	if (Sw1) LED1 = 1;
	else
	{
		// Turn all LEDs off
		LED1 = 0;
	
		for (cnt = 0; cnt < BTN_NUMBER; cnt++)
		{
			BtnArray[cnt].LEDR = 0;
			BtnArray[cnt].LEDY = 0;
			BtnArray[cnt].LEDG = 0;
		}
	}
}

R_TRIG_typ set_R_TRIG(R_TRIG_typ Rset, BOOL CLK)
{
	Rset.CLK = CLK;
	R_TRIG(&Rset);
	return Rset;
}

TON_typ set_TON(TON_typ TONset, BOOL IN)
{
	TONset.IN = IN;
	TONset.PT = BtnDelay;
	TON(&TONset);
	return TONset;
}

void toggleLED(int index)
{
	BtnArray[index].LEDR = !BtnArray[index].LEDR;
	BtnArray[index].LEDG = !BtnArray[index].LEDG;
}
