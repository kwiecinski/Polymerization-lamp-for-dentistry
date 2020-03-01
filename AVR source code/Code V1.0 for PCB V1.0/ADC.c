#include	<avr/io.h>
#include	"ADC.h"

//-----------------------------------------------------------------------------------------------------------------
void ADC_init(void)
{
	//ustawienia ADC
	ADMUX |= (1<<REFS0);	//napiêcie odniesienia wewnêtrzne 1,1V
	ADCSRA |= (1<<ADEN)| (1<<ADPS2)| (1<<ADPS0);  //w³¹czenie ADC, preskaler 128
}


//-----------------------------------------------------------------------------------------------------------------
/*
 *
 * Returning voltage in format: ex. 15364 ->1,5364V
 *
 */
uint16_t ADC_measure(uint8_t channel)
{
	const uint16_t RefVoltage=108;
	const uint8_t samples=50;
	uint8_t MSB,LSB,LoopCounter;
	uint16_t voltage,sum;
	uint32_t ADC_result;


	ADMUX |=(ADMUX & 0xF8) | channel;
	sum=0;

	for(LoopCounter=0;LoopCounter<samples;LoopCounter++)
	{
		ADCSRA |=(1<<ADSC);
		while(ADCSRA & (1<<ADSC));	//czekam na dokonanie pomiaru

		LSB=ADCL;	//odczyt danych z ADC
		MSB=ADCH;

		ADC_result=(uint16_t)MSB<<8 | (uint16_t)LSB;
		sum=sum+ADC_result;
	}

	ADC_result=sum/(uint16_t)samples;
	ADC_result=ADC_result*100;
	voltage=(ADC_result/1024)*RefVoltage;

	return voltage;
}
