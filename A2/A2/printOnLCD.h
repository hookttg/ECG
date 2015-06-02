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

volatile static bool calculateSDNN = false;

void updateLCD () {
	
 	returnLCD();
 	
 	printTimeElapsed();
 	
 	display(' '); // space
 	
 	printNumberOfBeats();
 	
 	display(' '); // space
 	
 	printHeartRate();
 	
 	moveToNextLine();
 	
 	printMNN();
	 
	printSDNN();
	
}

void printTimeElapsed () {
		
		display('T');
		
		int minInBits = min;
		minInDigits[0] = (minInBits%10)+'0';
		minInDigits[1] = ((minInBits%100-minInBits%10)/10)+'0';
		
		display(minInDigits[0]);
		display(':');
		
		int secInBits = sec;
		secInDigits[0] = (secInBits%10)+'0';
		secInDigits[1] = ((secInBits%100-secInBits%10)/10)+'0';
		
		display(secInDigits[1]);
		display(secInDigits[0]);		// Display number of digits
				
}

void printNumberOfBeats () {
		
		display('B');
		
		int beatsInBits = numberOfHeartBeats;
		beatsInDigits[0] = (beatsInBits%10)+'0';
		beatsInDigits[1] = ((beatsInBits%100-beatsInBits%10)/10)+'0';
		beatsInDigits[2] = ((beatsInBits%1000-beatsInBits%100)/100)+'0';
		
		display(beatsInDigits[2]);
		display(beatsInDigits[1]);
		display(beatsInDigits[0]);		// Display number of digits

}

void printHeartRate () {
	
		display('H');
		display('R');
	
		if (calculateHeartRate==true) {
			
			HR = (heartBeatInLast15Sec*60)/15;
			heartBeatInLast15Sec = 0; // reset this every 15 seconds to count the number of beats for next 15 seconds
			
		}
	
		calculateHeartRate = false;
		
		HRinDigits[0] = (HR%10)+'0';
		HRinDigits[1] = ((HR%100-HR%10)/10)+'0';
		HRinDigits[2] = ((HR%1000-HR%100)/100)+'0';
	
		display(HRinDigits[2]);
		display(HRinDigits[1]);
		display(HRinDigits[0]);

}


void printMNN () {
	
	if (calculateMNN==true) {
 
		MNN = sumOFTimeIntervalsForAllBeats/(heartBeatTrackerForMNN-1); // MNN will be calculated every 15 seconds
		sumOFTimeIntervalsForAllBeats = 0;
		heartBeatTrackerForMNN = 0;
		calculateMNN = false;
		indexOfTimeIntervalVector = 0;
		
		calculateSDNN = true;
	}
	
	MNNinDigits[0] = (MNN%10)+'0';
	MNNinDigits[1] = ((MNN%100-MNN%10)/10)+'0';
	MNNinDigits[2] = ((MNN%1000-MNN%100)/100)+'0';
	MNNinDigits[3] = ((MNN%10000-MNN%1000)/1000)+'0';
	
	display('M');
	display('N');
	display('N');
	//display(':');
	
	display(MNNinDigits[3]);
	display('.');
	display(MNNinDigits[2]);
	display(MNNinDigits[1]);
	display(MNNinDigits[0]);
	
	
}


void printSDNN () {
	
	int i, diff, sq =0;
	
	if (calculateSDNN==true) {
		
		for (i = 0; i < indexOfTimeIntervalVector; i++) {
			
			diff = (timeIntervalForAllBeats[i] - MNN);
			
			sq += (diff*diff); // = (diff)^2
			
		}
		
		variance = sq/(indexOfTimeIntervalVector-1);
		calculateSDNN = false;
		SDNN = sqrt(variance);
		
	}	
	
	
	
	SDNNinDigits[0] = (SDNN%10)+'0';
	SDNNinDigits[1] = ((SDNN%100-SDNN%10)/10)+'0';
	SDNNinDigits[2] = ((SDNN%1000-SDNN%100)/100)+'0';
	SDNNinDigits[3] = ((SDNN%10000-SDNN%1000)/1000)+'0';
	
	display(' ');
	display('S');
	display('D');
	
	display(SDNNinDigits[3]);
	display('.');
	display(SDNNinDigits[2]);
	display(SDNNinDigits[1]);
	display(SDNNinDigits[0]);
	
	}

#endif /* PRINTONLCD_H_ */