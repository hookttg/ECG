/*
 * timer.h
 *
 * Created: 27/05/2015 9:00:10 pm
 *  Author: Tanzim
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "heartBeatDetector.h"
 
volatile static int count=0;
volatile static int sec=0;
volatile static int min=0;
volatile static int hours=0;
volatile static int t =0;

typedef int bool; // boolean value (1=true, 0=False)
#define true 1
#define false 0

volatile static bool calulateHeartRate = false; // This will be set to true every 15 seconds and HR will be calculated

ISR(TIMER0_OVF_vect)
{
	TCNT0=241;
	count++;
	
	if (count>=1000){
		sec++;
		t++;
		count=0;
		updateLCD();
	}
	
	if (t==15){ // this will assist HR calculator to keep track of beats in last 15 seconds
		t=0;
		calulateHeartRate = true; // this will alert the the HR calculator
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