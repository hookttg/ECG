/*
 * heartBeatDetector.h
 *
 * Created: 27/05/2015 8:46:14 pm
 *  Author: Tanzim
 */ 


#ifndef HEARTBEATDETECTOR_H_
#define HEARTBEATDETECTOR_H_


unsigned char  adc_data;
int lastSignal=0;
int currentSignal=0;
volatile static int numberOfHeartBeats=0; // this will be used to track total number of beats
volatile static int heartBeatTrackerForMNN = 0; // this will be used to calculate MNN and it will get reset every 4 seconds
volatile static int heartBeatInLast15Sec=0;
#include "timer.h"

ISR(ADC_vect)
{
	
	adc_data = ADCH;	// read adc data
	//adc_data = adc_data-512; // to calculate the energy of signal, we subtract it by 512
	
	if (adc_data > 2.9) {
		PORTB=0b1111111;
		//display('1');
		
		currentSignal = 1;
		if (lastSignal==currentSignal){
			//display('2');
		}else{
			lastSignal = currentSignal;
			numberOfHeartBeats++;
			heartBeatTrackerForMNN++;
			heartBeatInLast15Sec++; // this will be set to 0 at t=15 in timer function
			storeTimeIntervalBetweenLastTwoBeats();
			updateLCD();
		}
		
	}
	else {
		lastSignal=0;
		PORTB=0b11111110;
		//display('0');
		//_delay_ms(100);
		//initialLCD();
		//returLCD();
		
	}
	ADCSRA = ADCSRA | 0x40; // start next ADC conversion
}



#endif /* HEARTBEATDETECTOR_H_ */