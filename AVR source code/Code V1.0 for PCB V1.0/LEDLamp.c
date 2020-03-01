#include <avr/io.h>
#include "LEDLamp.h"
#include "TimerISR.h"
#include "ADC.h"
#include "define.h"

//-----------------------------------------------------------------------------------------------------------------

void MAIN_Init (MAINSTRUCT *ptr)
{
	DDRB |= LED|BUZZ|FAN; 	//Konfiguracja pinów jako wyjœcia
	DDRB  &= ~(TERM_PIN|SWITCH);	//Konfiguracja pinów jako wejœcia

	//ustalenie stanów pocz¹tkowych portów
	buzz_off;
	fan_off;
	led_off;

	ISR_init();
	ADC_init();

	Timer1=0;


	ptr->ledstat=true;
	ptr->timerflag=false;
	ptr->fanlock=false;
	ptr->buzzflag=false;
	ptr->buzzon=false;
	ptr->buzz10flag=false;

}

//-----------------------------------------------------------------------------------------------------------------

void KeyPress(MAINSTRUCT *ptr)
{

	if(!ptr->klock && !SWITCH_PUSH)
	{
		if(!ptr->timerflag)
		{
			Timer1=3;
			ptr->timerflag=true;
		}else
		{
			if(!Timer1 && !SWITCH_PUSH)
			{
				ptr->timerflag=false;
				ptr->klock=true;
				LedDrive(ptr);

			}
		}



	}else if(ptr->klock && SWITCH_PUSH)
	{
		if(!ptr->timerflag)
		{
			Timer1=3;
			ptr->timerflag=true;
		}else
		{
			if(!Timer1)
			{
				ptr->klock=false;
				ptr->timerflag=false;
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------

void LedDrive(MAINSTRUCT *ptr)
{

	if(ptr->ledstat)
	{
		led_on;
		ptr->ledstat=false;
		ptr->buzztime=7;
		ptr->buzzon=true;
	}else
	{
		led_off;
		ptr->ledstat=true;
		ptr->buzztime=7;
		ptr->buzzon=true;
	}

}

//-----------------------------------------------------------------------------------------------------------------

void TempCheck(MAINSTRUCT *ptr)
{
	if(!Timer2)
	{
		if(!ptr->ledstat)
		{
			if(!ptr->fanlock)
			{
				if(ADC_measure(TERM_CHL)<8500)		//temp 35oC
				{

					fan_on;
					ptr->fanlock=true;
				}
			}
		}
		if(ptr->fanlock)
		{
			if(ADC_measure(TERM_CHL)>9400)
			{
				fan_off;
				ptr->fanlock=false;
			}
		}

		Timer2=40;
	}
}

//-----------------------------------------------------------------------------------------------------------------
void BuzzerDrive(MAINSTRUCT *ptr)
{
	if(!ptr->buzzflag && ptr->buzzon)
	{
		buzz_on;
		Timer3=ptr->buzztime;
		ptr->buzzflag=true;

	}else if(!Timer3 && ptr->buzzflag)
	{
		buzz_off;
		ptr->buzzflag=false;
		ptr->buzzon=false;
	}
}

//-----------------------------------------------------------------------------------------------------------------

void Buzzer10sCheck(MAINSTRUCT *ptr)
{

	if(!ptr->ledstat && !ptr->buzz10flag)
	{
		Timer4=368;
		ptr->buzz10flag=true;

	}else if(!Timer4 && ptr->buzz10flag)
	{
		ptr->buzztime=18;
		ptr->buzzon=true;
		ptr->buzz10flag=false;

	}else if(ptr->ledstat)
	{
		ptr->buzz10flag=false;
	}

}
