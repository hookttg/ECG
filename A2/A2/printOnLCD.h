/*
 * printOnLCD.h
 *
 * Created: 27/05/2015 9:19:17 pm
 *  Author: Tanzim
 */ 


#ifndef PRINTONLCD_H_
#define PRINTONLCD_H_
#include "heartBeatDetector.h"
static unsigned char secInBits[2];		// vector saves the amount of letters (in 2 bits)
static unsigned char beats[3]; // this vector stores the digits for time elapsed in bits

void updateLCD () {
	returnLCD();
	
	display('T');
	display(':');
	showTimeElapsed();
	showNumberOfBeats();
	
	
	
	
}

void showTimeElapsed () {
		
		int sBits = sec;
		secInBits[0] = (sBits%10)+'0';
		secInBits[1] = ((sBits%100-sBits%10)/10)+'0';
		//secInBits[2] = ((NLb%1000-NLb%100)/100)+'0';	//get each bit's value of letter_num
		//startLCD();
		//returnLCD();
		//PORTD=0b10000000; //command 4: clear screen
		display(secInBits[1]);
		display(secInBits[0]);		// Display number digits
}

void showNumberOfBeats () {
	
		display(' ');
		display('B');
		display(':');
		int beatsInBits = heartBeat;
		beats[0] = (beatsInBits%10)+'0';
		beats[1] = ((beatsInBits%100-beatsInBits%10)/10)+'0';
		beats[2] = ((beatsInBits%1000-beatsInBits%100)/100)+'0';	//get each bit's value of letter_num
		//initialLCD();	// These two lines make a new page
		//returnLCD();	//and move cursor to first position
	
		display(beats[2]);
		display(beats[1]);
		display(beats[0]);		// Display number of digits

}





#endif /* PRINTONLCD_H_ */