
TYPE
	door_t : 	STRUCT 
		button_outside : BOOL;
		button_inside : BOOL;
		sensor_closed : BOOL;
		sensor_opened : BOOL;
		sensor_barrier : BOOL;
		motor_opening : BOOL;
		motor_closing : BOOL;
		display : BOOL;
		timer : TON;
		timer_display : TON;
	END_STRUCT;
END_TYPE
