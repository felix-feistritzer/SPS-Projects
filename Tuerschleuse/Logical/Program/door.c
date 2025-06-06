#include "door.h"

void door_display(door_t* self, TIME blink_speed)
{
	self->timer.IN = TRUE;
	
	if (self->timer.Q)
	{
		self->display = !(self->display);
		self->timer.IN = FALSE;
	}
	
	self->timer = set_TON(self->timer, self->timer.IN, blink_speed);
}

TON_typ set_TON(TON_typ TONset, BOOL in, TIME delay)
{
	TONset.IN = in;
	TONset.PT = delay;
	TON(&TONset);
	return TONset;
}
