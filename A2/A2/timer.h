/*
 * timer.h
 *
 * Created: 27/05/2015 9:00:10 pm
 *  Author: Tauseef (u4858965)
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "heartBeatDetector.h"

volatile static int count=0;
volatile static int sec=0;
volatile static int min=0;
volatile static int hours=0;
volatile static int timerForCalculatingHR =0;
volatile static int timerForCalculatingMNN = 0;

volatile static int timeIntervalBetweenLastTwoBeats = 0; // This will track time for R-R interval. I will store these values in an array and then calculate MNN/MRR
volatile static int timeIntervalForAllBeats[100]; // This vector will store the time intervals for the detected beats
volatile static int sumOFTimeIntervalsForAllBeatsInLastFourSeconds = 0;
volatile static int indexOfTimeIntervalVector = 0;

static unsigned int secInDigits[2];		// vector saves the amount of letters (in 2 bits)
static unsigned int minInDigits[2];

typedef int bool; // boolean value (1=true, 0=False)
#define true 1
#define false 0

volatile static bool calculateHeartRate = false; // This will be set to true every 15 seconds and HR will be calculated
volatile static bool calculateMNN = false;
volatile static bool calculateSDNN = false;

ISR(TIMER0_OVF_vect)
{
	TCNT0=241;
	count++;
	timeIntervalBetweenLastTwoBeats++;
	
	if (count>=1000){
		sec++;
		timerForCalculatingHR++; // HR will be calculated when the value for this is 15.
		timerForCalculatingMNN++;
		count=0;
		updateLCD();
	}
	
	if (timerForCalculatingHR==15){ // this will assist HR calculator to keep track of beats in last 15 seconds

		calculateHeartRate = true; // this will alert the the HR function to calculate HR
		timerForCalculatingHR=0; // when t=15, reset this to zero

	}
	
	if (timerForCalculatingMNN==4) {
		
		calculateMNN = true;
		timerForCalculatingMNN = 0;
		
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

storeTimeIntervalBetweenLastTwoBeats () {
	
	// the next few lines will be used for calculating SD
	
	int index = indexOfTimeIntervalVector;
	
	timeIntervalForAllBeats[index] = timeIntervalBetweenLastTwoBeats;
	
	timeIntervalBetweenLastTwoBeats = 0; // start counting again for next beat
	
	indexOfTimeIntervalVector++; // this will be set to 0 every time MNN is calculated
	
}


void printTimeElapsed () {
	
	print('T');
	
	// the LCD displays data bit by bit. So I am separating the decimal value to 3 bits.
	
	int minInBits = min;
	
	minInDigits[0] = (minInBits%10)+'0'; // Print function takes input char. So i am adding zero to "int" inorder to convert the value to char.
	minInDigits[1] = ((minInBits%100-minInBits%10)/10)+'0';
	
	print(minInDigits[0]);
	print(':');
	
	int secInBits = sec;
	secInDigits[0] = (secInBits%10)+'0';
	secInDigits[1] = ((secInBits%100-secInBits%10)/10)+'0';
	
	print(secInDigits[1]);
	print(secInDigits[0]);
	print(' '); // space
	
}


#endif /* TIMER_H_ */