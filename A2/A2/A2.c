/* 
 Name: Tauseef 
 Uni ID: u4858965
 Group: 58
 
 Tasks completed: 
  - identify basic waves
  - identify 180 bpm
  - calculate MNN and SDNN 
  
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

#include "myLCD.h"
#include "heartBeatDetector.h"
#include "timer.h"
#include "updateLCD.h"
#include "initialize.h"


int main(void) {
	
	initialize(); // this function is from initialze.h
	
	while(1) {
		
		clearLCD(); // this function is from myLCD.h
		
		printTimeElapsed(); // this function is from updateLCD.h  This will start the timer and update the LCD every second
		
		printNumberOfBeats(); // this function is from heartBeatDetector.h  This function will count the number of beats and print the value on the LCD everytime a new value is detected
		
		printHeartRate(); // this function is from heartBeatDetector.h  This function will calculate the HR every 15 sec and print the value on LCD
		
		moveToNextLine(); // this function is from myLCD.h
		
		printMNN(); // this function is from MNNCalculator.h  This will calculate MNN every 4 sec and print the value on LCD
		
		printSDNN(); // this function is from SdnnCalculator.h  This will calculate SDNN every 4 sec and print it on the LCD
		
	}
	
}