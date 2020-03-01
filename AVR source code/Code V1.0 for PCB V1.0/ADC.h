/*
 * ADC.h
 *
 *  Created on: 20 sty 2019
 *      Author: senio
 */

#ifndef ADC_H_
#define ADC_H_

#define TERM_PIN 		(1<<PB4)
#define TERM_CHL		2		//PB4 (ADC2)


uint16_t ADC_measure(uint8_t channel);
void ADC_init(void);

#endif /* ADC_H_ */
