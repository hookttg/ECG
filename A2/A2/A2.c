
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

#include "myLCD.h"
#include "heartBeatDetector.h"
#include "timer.h"
#include "printOnLCD.h"


int main(void)
{
	
	DDRB = 0b11111111;	// Set all pins of PORTB as output
	DDRD = 0b11111111;	// Set all pins of PORTD as output
	ADMUX = 0x40;		//Choose 5V VCC as reference voltage and select ADC0 as channel
	ADCSRA = 0xCD;		//Start ADC conversion and set ADC prescalar to 128
	TCCR0 = 0x05;		//Set prescalr to 1024
	TCNT0 = 0;			// set 0 as initial value of timer0
	TIMSK = 0x01;	    //unmask  timer0 overflow interrupt
			
	startLCD();	// call this function to initial LCD screen
	//returnLCD();	// call this function to move cursor to first (initial) position
			
	asm("sei");   // enable global interrupt
	
	
	while(1){
		updateLCD();
	}

}