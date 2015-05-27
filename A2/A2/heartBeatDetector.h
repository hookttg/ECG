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
volatile static int beat=0;
volatile static int count=0;
static unsigned char beats[3]; // this vector stores the digits for time elapsed in bits


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



#endif /* HEARTBEATDETECTOR_H_ */