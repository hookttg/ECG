/*
 * printOnLCD.h
 *
 * Created: 27/05/2015 9:19:17 pm
 *  Author: Tanzim
 */ 


#ifndef PRINTONLCD_H_
#define PRINTONLCD_H_
#include "heartBeatDetector.h"


static unsigned char secInDigits[2];		// vector saves the amount of letters (in 2 bits)
static unsigned char minInDigits[2];
static unsigned char beatsInDigits[3]; // this vector stores the digits for time elapsed in bits
static unsigned char HRinDigits[3];
volatile static int HR=0;

void updateLCD () {
	returnLCD();
	
	display('T');
	//display(':');
	showTimeElapsed();
	
	display(' ');
	showNumberOfBeats();
	
	display(' ');
	showHeartRate();
	
	//_delay_ms(200);
	
}

void showTimeElapsed () {
		
		int minInBits = min;
		minInDigits[0] = (minInBits%10)+'0';
		minInDigits[1] = ((minInBits%100-minInBits%10)/10)+'0';
		
		//display(minInDigits[1]);
		display(minInDigits[0]);
		display(':');
		int secInBits = sec;
		secInDigits[0] = (secInBits%10)+'0';
		secInDigits[1] = ((secInBits%100-secInBits%10)/10)+'0';
		//secInBits[2] = ((NLb%1000-NLb%100)/100)+'0';	//get each bit's value of letter_num
		//startLCD();
		//returnLCD();
		//PORTD=0b10000000; //command 4: clear screen
		display(secInDigits[1]);
		display(secInDigits[0]);		// Display number digits
				
}

void showNumberOfBeats () {
	
		display('B');
		//display(':');
		int beatsInBits = heartBeat;
		beatsInDigits[0] = (beatsInBits%10)+'0';
		beatsInDigits[1] = ((beatsInBits%100-beatsInBits%10)/10)+'0';
		beatsInDigits[2] = ((beatsInBits%1000-beatsInBits%100)/100)+'0';
		
		display(beatsInDigits[2]);
		display(beatsInDigits[1]);
		display(beatsInDigits[0]);		// Display number of digits

}

void showHeartRate () {
	
		display('H');
		display('R');
	
		if (calulateHeartRate==true) {
			
			HR = (heartBeatInLast15Sec*60)/15;
			heartBeatInLast15Sec = 0; // reset this every 15 seconds to count the number of beats for next 15 seconds
			
		}
	
		calulateHeartRate = false;
		
		HRinDigits[0] = (HR%10)+'0';
		HRinDigits[1] = ((HR%100-HR%10)/10)+'0';
		HRinDigits[2] = ((HR%1000-HR%100)/100)+'0';
	
		display(HRinDigits[2]);
		display(HRinDigits[1]);
		display(HRinDigits[0]);

}




#endif /* PRINTONLCD_H_ */