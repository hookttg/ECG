/*
 * timer.h
 *
 * Created: 27/05/2015 9:00:10 pm
 *  Author: Tanzim
 */ 


#ifndef TIMER_H_
#define TIMER_H_
 
volatile static int count=0;
volatile static int sec=0;
volatile static int min=0;
volatile static int hours=0;

ISR(TIMER0_OVF_vect)
{
	TCNT0=241;
	count++;
	
	if (count>=1000){
		sec++;
		count=0;
		updateLCD();
	}
	
	if (sec>=60){
		min++;
		sec=0;
	}
	
	if (min>=60){
		hours++;
		min=0;
	}
}



#endif /* TIMER_H_ */