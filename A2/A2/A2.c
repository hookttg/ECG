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
#include "printOnLCD.h"
#include "initialize.h"


int main(void) {
	
	initialize(); // this function is from initialze.h
	
	while(1) {
		
		clearLCD(); // this function is from myLCD.h
		
		printTimeElapsed(); // this function is from printOnLCD.h
		
		printNumberOfBeats(); // this function is from heartBeatDetector.h
		
		printHeartRate(); // this function is from heartBeatDetector.h
		
		moveToNextLine(); // this function is from myLCD.h
		
		printMNN(); // this function is from MNNCalculator.h
		
		printSDNN(); // this function is from SdnnCalculator.h
		
	}
	

}