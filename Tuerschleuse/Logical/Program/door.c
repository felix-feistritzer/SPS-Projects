#include "door.h"

void door_display(door_t* self, TIME blink_speed)
{
	self->timer_display.IN = TRUE;
	
	if (self->timer_display.Q)
	{
		self->display = !(self->display);
		self->timer_display.IN = FALSE;
	}
	
	self->timer_display = set_TON(self->timer_display, self->timer_display.IN, blink_speed);
}

TON_typ set_TON(TON_typ TONset, BOOL in, TIME delay)
{
	TONset.IN = in;
	TONset.PT = delay;
	TON(&TONset);
	return TONset;
}

TON_typ reset_TON(TON_typ TONset)
{
	return set_TON(door_1.timer, FALSE, SECOND);
}
