/*
 * printOnLCD.h
 *
 * Created: 27/05/2015 9:19:17 pm
 *  Author: Tanzim
 */ 


#ifndef PRINTONLCD_H_
#define PRINTONLCD_H_
#include "heartBeatDetector.h"


static unsigned int secInDigits[2];		// vector saves the amount of letters (in 2 bits)
static unsigned int minInDigits[2];
static unsigned int beatsInDigits[3]; // this vector stores the digits for time elapsed in bits
static unsigned int HRinDigits[3];
volatile static int HR=0;
volatile unsigned int MNNinDigits[4];
volatile unsigned int SDNNinDigits[4];
volatile static unsigned int MNN = 0;
volatile static unsigned int SDNN = 0;
volatile static int sumOfTimeIntervals = 0;
volatile static unsigned int variance = 0;

#include "MNNCalculator.h"
#include "SdnnCalculator.h"


void updateLCD () {
	
 	clearLCD();
 	
 	printTimeElapsed();
 	
 	printNumberOfBeats();
 	
 	printHeartRate();
 	
 	moveToNextLine();
 	
 	printMNN();
	 
	printSDNN();
	
}

void printTimeElapsed () {
		
		print('T');
		
		int minInBits = min;
		minInDigits[0] = (minInBits%10)+'0';
		minInDigits[1] = ((minInBits%100-minInBits%10)/10)+'0';
		
		print(minInDigits[0]);
		print(':');
		
		int secInBits = sec;
		secInDigits[0] = (secInBits%10)+'0';
		secInDigits[1] = ((secInBits%100-secInBits%10)/10)+'0';
		
		print(secInDigits[1]);
		print(secInDigits[0]);		// Display number of digits
		print(' '); // space
				
}

void printNumberOfBeats () {
		
		print('B');
		
		int beatsInBits = numberOfHeartBeats;
		beatsInDigits[0] = (beatsInBits%10)+'0';
		beatsInDigits[1] = ((beatsInBits%100-beatsInBits%10)/10)+'0';
		beatsInDigits[2] = ((beatsInBits%1000-beatsInBits%100)/100)+'0';
		
		print(beatsInDigits[2]);
		print(beatsInDigits[1]);
		print(beatsInDigits[0]);		// Display number of digits
		
		print(' '); // space

}

void printHeartRate () {
	
		print('H');
		print('R');
	
		if (calculateHeartRate==true) {
			
			HR = (heartBeatInLast15Sec*60)/15;
			heartBeatInLast15Sec = 0; // reset this every 15 seconds to count the number of beats for next 15 seconds
			
		}
	
		calculateHeartRate = false;
		
		HRinDigits[0] = (HR%10)+'0';
		HRinDigits[1] = ((HR%100-HR%10)/10)+'0';
		HRinDigits[2] = ((HR%1000-HR%100)/100)+'0';
	
		print(HRinDigits[2]);
		print(HRinDigits[1]);
		print(HRinDigits[0]);

}




#endif /* PRINTONLCD_H_ */