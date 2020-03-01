#ifndef LEDLAMP_H_
#define LEDLAMP_H_

typedef struct
{
	uint8_t klock,
			timerflag,
			ledstat,
			fanlock,
			buzzflag,
			buzzon,
			buzz10flag,
			buzztime;

}MAINSTRUCT;

void LedDrive(MAINSTRUCT *ptr);
void KeyPress(MAINSTRUCT *ptr);
void TempCheck(MAINSTRUCT *ptr);
void BuzzerDrive(MAINSTRUCT *ptr);
void Buzzer10sCheck(MAINSTRUCT *ptr);
void MAIN_Init (MAINSTRUCT *ptr);


#endif /* LEDLAMP_H_ */
