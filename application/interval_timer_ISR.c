extern volatile int timeout;

/*****************************************************************************
 * Interval timer interrupt service routine
 *                                                                          
 * Controls refresh of the VGA screen
 * 
******************************************************************************/
void interval_timer_ISR( )
{
	volatile int * interval_timer_ptr = (int *) 0x10002000;

	*(interval_timer_ptr) = 0; 										// clear the interrupt
	timeout = 1;															// set global variable

	return;
}

