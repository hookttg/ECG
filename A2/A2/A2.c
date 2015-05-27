
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "myLCD.h"
#define F_CPU 16000000UL

volatile static int beat=0;
volatile static int count=0;
volatile static int sec=0;
volatile static int min=0;

unsigned char  adc_data;
int lastSignal=0;
int currentSignal=0;

static unsigned char beats[3]; // this vector stores the digits for time elapsed in bits




ISR(TIMER0_OVF_vect)
{
	
//test

}

ISR(ADC_vect)
{
	
	adc_data = ADCH;	// read adc data
	//adc_data = adc_data-512; // to calculate the energy of signal, we subtract it by 512
	
	if (adc_data > 0.8) {
		PORTB=0b1111111;
		//display('1');
		
		currentSignal = 1;
		if (lastSignal==currentSignal){
			//display('2');
		}else{
			lastSignal = currentSignal;
			int beatsInBits = count++;
			beats[0] = (beatsInBits%10)+'0';
			beats[1] = ((beatsInBits%100-beatsInBits%10)/10)+'0';
			beats[2] = ((beatsInBits%1000-beatsInBits%100)/100)+'0';	//get each bit's value of letter_num
			initialLCD();	// These two lines make a new page
			returnLCD();	//and move cursor to first position
			
			display(beats[2]);
			display(beats[1]);
			display(beats[0]);		// Display number of digits
			//_delay_ms(200);
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



int main(void)
{
	
	DDRB = 0b11111111;	// Set all pins of PORTB as output
	DDRD = 0b11111111;	// Set all pins of PORTD as output
	ADMUX = 0x40;		//Choose 5V VCC as reference voltage and select ADC0 as channel
	ADCSRA = 0xCF;		//Start ADC conversion and set ADC prescalar to 128
	TCCR0 = 0x05;		//Set prescalr to 1024
	TCNT0 = 0;			// set 0 as initial value of timer0
	TIMSK = 0x01;	    //unmask  timer0 overflow interrupt
			
	initialLCD();	// call this function to initial LCD screen
	returnLCD();	// call this function to move cursor to first (initial) position
			
	asm("sei");   // enable global interrupt
	
	
	while(1){
		
	}

}