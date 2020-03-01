#include	<avr/io.h>
#include 	<avr/interrupt.h>
#include	"define.h"
#include	"TimerISR.h"

//-----------------------------------------------------------------------------------------------------------------
void ISR_init(void)
{

	/*
	 * TIMER0 init
	 * 9,6MHz clock and prescaler 1024 - increment registe 9375Hz (106,6us)
	 * ISR fire: 106,6*OCRA
	 */

	//konfiguracja TIMER0
	OCR0A = 255; //100Hz (0,01s)
	TCCR0A |= (1 << WGM01); // Configure timer 1 for CTC mode
 	TCCR0B |= (1 << CS02)|(1 << CS00);		//presc 1024
    TIMSK0 |= (1 << OCIE0A);

	sei();

}
//-----------------------------------------------------------------------------------------------------------------
ISR(TIM0_COMPA_vect) ///27,2ms
{
	if (Timer1!=0)
	{
		Timer1--;
	}

	if (Timer2!=0)
	{
		Timer2--;
	}

	if(Timer3!=0)
	{
		Timer3--;
	}

	if(Timer4!=0)
	{
		Timer4--;
	}

 }
