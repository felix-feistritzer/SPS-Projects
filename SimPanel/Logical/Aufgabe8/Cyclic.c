
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define BTN_NUMBER 	4
#define DELAY		1000 // ms

R_TRIG_typ set_R_TRIG(R_TRIG_typ Rset, BOOL CLK);
TON_typ set_TON(TON_typ Tset, BOOL IN);
void toggleLEDshort(int index);
void toggleLEDlong(int index);

void _CYCLIC ProgramCyclic(void)
{
	int cnt;
	
	// Dedect Rising Edge of Switch 1
	Sw1_Rise = set_R_TRIG(Sw1_Rise, Sw1);
	
	// Dedect Rising Edge of Buttons 3-6
	for (cnt = 0; cnt < BTN_NUMBER; cnt++)
	{
		// short Rising Edge
		BtnArray[cnt].Btn_Rise = set_R_TRIG(BtnArray[cnt].Btn_Rise, BtnArray[cnt].Btn);
		
		// long Rising Edge
		BtnArray[cnt].Btn_TOn = set_TON(BtnArray[cnt].Btn_TOn, BtnArray[cnt].Btn);
		BtnArray[cnt].Btn_LongRise = set_R_TRIG(BtnArray[cnt].Btn_LongRise, BtnArray[cnt].Btn_TOn.Q);
	}
	
	// Switch 1 turned on -> all yellow LEDs on
	if (Sw1_Rise.Q)
	{
		for(cnt = 0; cnt < BTN_NUMBER; cnt++)
		{
			BtnArray[cnt].LEDY = 1;
		}
	}
	
	// Check for short and long Button Press -> Toggle LED
	for (cnt = 0; cnt < BTN_NUMBER; cnt++)
	{
		if (Sw1 && BtnArray[cnt].Btn_Rise.Q)
		{
			toggleLEDshort(cnt);
		}
		if (Sw1 && BtnArray[cnt].Btn_LongRise.Q)
		{
			toggleLEDlong(cnt);
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
	TONset.PT = DELAY;
	TON(&TONset);
	return TONset;
}

void toggleLEDshort(int index)
{
	if (BtnArray[index].LEDY == 1)
	{
		BtnArray[index].LEDR = 0;
		BtnArray[index].LEDY = 0;
		BtnArray[index].LEDG = 1;
	}
	else
	{
		BtnArray[index].LEDR = 0;
		BtnArray[index].LEDY = 1;
		BtnArray[index].LEDG = 0;
	}
}

void toggleLEDlong(int index)
{
	BtnArray[index].LEDR = 1;
	BtnArray[index].LEDY = 0;
	BtnArray[index].LEDG = 0;
}
