/*
 * define.h
 *
 *  Created on: 25 lis 2018
 *      Author: senio
 */
#define 	F_CPU   9600000UL

#define LED (1<<PB3)
#define led_off PORTB |= LED
#define led_on PORTB &= ~LED

#define BUZZ (1<<PB0)
#define buzz_on PORTB |= BUZZ
#define buzz_off PORTB &= ~BUZZ

#define FAN (1<<PB2)
#define fan_off PORTB |= FAN
#define fan_on PORTB &= ~FAN

#define SWITCH (1<<PB1)
#define SWITCH_PUSH (PINB & SWITCH)

#define true	1
#define false	0

