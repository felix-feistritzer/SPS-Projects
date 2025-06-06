
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#define BTN_NUMBER 4

R_TRIG_typ set_R_TRIG(R_TRIG_typ Rset, BOOL CLK);

void toggleLED(int index);

void _CYCLIC ProgramCyclic(void)
{
	int cnt;
	
	// Dedect Rising Edge of Switch 1
	Sw1_Rise = set_R_TRIG(Sw1_Rise, Sw1);
	
	// Dedect Rising Edge of Buttons 3-6
	for (cnt = 0; cnt < BTN_NUMBER; cnt++)
	{
		BtnArray[cnt].Btn_Rise = set_R_TRIG(BtnArray[cnt].Btn_Rise, BtnArray[cnt].Btn);
	}
	
	// Switch 1 turned on -> all red LEDs on
	if (Sw1_Rise.Q)
	{
		for(cnt = 0; cnt < BTN_NUMBER; cnt++)
		{
			BtnArray[cnt].LEDR = 1;
		}
	}
	
	// Check for Button Press -> Toggle LED
	for (cnt = 0; cnt < BTN_NUMBER; cnt++)
	{
		if (Sw1 && BtnArray[cnt].Btn_Rise.Q)
		{
			toggleLED(cnt);
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

void toggleLED(int index)
{
	BtnArray[index].LEDR = !BtnArray[index].LEDR;
	BtnArray[index].LEDG = !BtnArray[index].LEDG;
}


