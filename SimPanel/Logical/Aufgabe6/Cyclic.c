
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define BTN_NUMBER 4

R_TRIG_typ set_R_TRIG(R_TRIG_typ Rset, BOOL CLK);
INT P_Value_100(INT P);

void _CYCLIC ProgramCyclic(void)
{
	int cnt;
	
	for (cnt = 0; cnt < BTN_NUMBER; cnt++)
	{
		BtnArray[cnt].Btn_Rise = set_R_TRIG(BtnArray[cnt].Btn_Rise, BtnArray[cnt].Btn);
	}
	
	// Switch 1
	if (Sw1)
	{
		LED1 = 1;
		DISP = P_Value_100(P1);
	}
	else
	{
		LED1 = 0;
	}
	
	// Switch 2
	if (Sw2)
	{
		LED2 = 1;
		DISP = P_Value_100(P2);
	}
	else
	{
		LED2 = 0;
	}
	
	if (!Sw1 && !Sw2)
	{
		// Sum
		if (BtnArray[0].Btn_Rise.Q)
		{
			DISP = P_Value_100(P1) + P_Value_100(P2);
		}
		// Difference
		if (BtnArray[1].Btn_Rise.Q)
		{
			DISP = P_Value_100(P1) - P_Value_100(P2);
		}
		// Product
		if (BtnArray[2].Btn_Rise.Q)
		{
			DISP = P_Value_100(P1) * P_Value_100(P2);
		}
		// Quotient
		if (BtnArray[3].Btn_Rise.Q && P_Value_100(P2) != 0)
		{
			DISP = P_Value_100(P1) / P_Value_100(P2);
		}
	}
}

R_TRIG_typ set_R_TRIG(R_TRIG_typ Rset, BOOL CLK)
{
	Rset.CLK = CLK;
	R_TRIG(&Rset);
	return Rset;
}

INT P_Value_100(INT P)
{
	return P / 327; // Values Range [0, 32767] => [0, 100]
}
