/*
 * heartBeatDetector.h
 *
 * Created: 27/05/2015 8:46:14 pm
 *  Author: Tauseef (u4858965)
 */ 


#ifndef HEARTBEATDETECTOR_H_
#define HEARTBEATDETECTOR_H_


unsigned char  adc_data;
int lastSignal=0;
int currentSignal=0;
volatile static int numberOfHeartBeats=0; // this will be used to track total number of beats
volatile static int heartBeatTrackerForMNN = 0; // this will be used to calculate MNN and it will get reset every 4 seconds
volatile static int heartBeatInLast15Sec=0;
static unsigned int beatsInDigits[3]; // this vector stores the digits for time elapsed in bits
volatile static int HR=0;
static unsigned int HRinDigits[3];

#include "timer.h"

ISR(ADC_vect)
{
	
	adc_data = ADCH;	// read adc data
	//adc_data = adc_data-512; // to calculate the energy of signal, we subtract it by 512
	
	if (adc_data > 2.9) {
		
		PORTB=0b1111111; // this will swith on the LED when heart beat is detected. In other words the LED will blink everytime a bit in detected
		
		
		currentSignal = 1;
		if (lastSignal==currentSignal){
			
		}else{
			
			lastSignal = currentSignal;
			
			numberOfHeartBeats++;
			heartBeatTrackerForMNN++;
			heartBeatInLast15Sec++; // this will be set to 0 at t=15 in timer function
			
			storeTimeIntervalBetweenLastTwoBeats(); // the stored values will be used to calculate MNN and SDNN. Stored values will be cleared every 4 seconds
			
			updateLCD();
			
		}
		
	}
	
	else {
		
		lastSignal=0;
		
		PORTB=0b11111110; // switch off LED if no heart beat detected. This will give the blinking effect 
		
	}
	
	ADCSRA = ADCSRA | 0x40; // start next ADC conversion
	
}

// the next function will print the number of beats on the LCD

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

// the next function will calculate and print Heart Rate

void printHeartRate () {
	
	if (calculateHeartRate==true) {
		
		HR = (heartBeatInLast15Sec*60)/15;
		heartBeatInLast15Sec = 0; // reset this every 15 seconds to count the number of beats for next 15 seconds
		
	}
	
	calculateHeartRate = false;
	
	// the LCD displays data bit by bit. So I am separating the decimal value to 3 bits.  
	
	HRinDigits[0] = (HR%10)+'0'; // Print function takes input char. So i am adding zero to "int" inorder to convert the value to char.
	HRinDigits[1] = ((HR%100-HR%10)/10)+'0';
	HRinDigits[2] = ((HR%1000-HR%100)/100)+'0';
	
	print('H');
	print('R');
	
	print(HRinDigits[2]);
	print(HRinDigits[1]);
	print(HRinDigits[0]);

}

#endif /* HEARTBEATDETECTOR_H_ */