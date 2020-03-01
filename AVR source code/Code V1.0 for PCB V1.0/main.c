#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "define.h"
#include "ADC.h"
#include "LEDLamp.h"
#include "TimerISR.h"

int main()
{
	MAINSTRUCT LedVar;

	MAIN_Init(&LedVar);

	while(true)
	{
		KeyPress(&LedVar);
		TempCheck(&LedVar);
		BuzzerDrive(&LedVar);
		Buzzer10sCheck(&LedVar);
	}

}





