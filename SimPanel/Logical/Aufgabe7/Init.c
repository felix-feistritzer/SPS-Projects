
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define BTN_NUMBER 4

void _INIT ProgramInit(void)
{
	// Set all outputs to Zero
	
	LED1 = 0;
	LED2 = 0;
	DISP = 0;
	
	int cnt;
	for (cnt = 0; cnt < BTN_NUMBER; cnt++)
	{
		BtnArray[cnt].LEDR = 0;
		BtnArray[cnt].LEDY = 0;
		BtnArray[cnt].LEDG = 0;
	}	
}