
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

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



void initialLCD()  // this function is used to initial LCD screen and it will be called in initial steps
{
	//setting up port direction on microprocessor
	DDRC=0b00110000; //portc has RS on bit 4, and enable on bit 5
	DDRD=0xFF;
	_delay_ms(100); //wait a little bit of time for the LCD to power up properly.
	
	//initialisation of LCD screen
	PORTC=0b00100000; //enable is high, RS is low (I'm going to send a command)
	_delay_ms(2);
	PORTD=0b00011100; //command1: function set (5x7 dot format, 2 line mode, 8-bit data)
	_delay_ms(2);
	PORTC=0b00000000; //enable is low, RS stays low (it will execute the command now)
	_delay_ms(2);
	PORTC=0b00100000; //enable is high, RS is low (I'm going to send another command)
	_delay_ms(2);
	PORTD=0b11110000; //command2: display on / cursor (Blink ON, underline ON, Display ON - you can use different settings if you like)
	_delay_ms(2);
	PORTC=0b00000000; //enable is low,  RS stays low (it will execute the command now)
	_delay_ms(2);
	PORTC=0b00100000; //enable is high, RS is low (I'm going to send another command)
	_delay_ms(2);
	PORTD=0b01100000; //command 3: character entry mode with increment and display shift OFF
	_delay_ms(2);
	PORTC=0b00000000; //enable is low, RS stays low (it will execute the command now)
	
	
	//now i am going to enter a real character
}
void returnLCD()   // this function is used to move the cursor to first (initial) position
{
	_delay_ms(2);
	PORTC=0b00100000; //enable is high, RS is low (I'm going to send another command)
	_delay_ms(2);
	PORTD=0b10000000; //command 4: clear screen
	_delay_ms(2);
	PORTC=0b00000000; //enable is low
	_delay_ms(2);
	PORTC=0b00100000; //enable is high
	_delay_ms(2);
	PORTD=0b01000000; //command 5 (take display cursor home)
	_delay_ms(2);
	PORTC=0b00000000; //enable is low
	_delay_ms(2);
	PORTC=0b00100000; //enable is high
	_delay_ms(5);
	// -.-.-

}

void display( char m )  // this function is used to display letters.	Input: variable m, type: char
// For example, display('A') will display letter 'A' on LCD screen
{
	_delay_ms(5);
	PORTC=0b00110000;
	//enable is high, with RS high (I'm going to send data)
	_delay_ms(5);
	switch(m)
	{
		case 'A':	{	PORTD=0b10000010;
	break;		}
	case 'B': 	{	PORTD=0B01000010;
break;		}
case 'C':   {	PORTD=0B11000010;
							break;		}
		case 'D':   {	PORTD=0b00100010;
							break;		}
		case 'E':   {	PORTD=0b10100010;	
							break;		}
		case 'F':	{	PORTD=0b01100010;
							break;		}
		case 'G': 	{	PORTD=0b11100010;
							break;		}		
		case 'H':   {	PORTD=0b00010010; 
							break;		}		
		case 'I':    {	PORTD=0b10010010; 
							break;		}	
		case 'J':    {	PORTD=0b01010010; 
							break;		}	
		case 'K':	{	PORTD=0b11010010; 
							break;		}	
		case 'L':	{	PORTD=0b00110010; 
							break;		}	
		case 'M':   {	PORTD=0b10110010; 
							break;		}	
		case 'N':   {	PORTD=0b01110010; 
							break;		}
		case 'O':	{	PORTD=0b11110010; 
							break;		}
	    case 'P':	{	PORTD=0b00001010; 
							break;		}
		case 'Q':   {	PORTD=0b10001010; 
							break;		}
		case 'R':	{	PORTD=0b01001010; 
							break;		}
		case 'S':	{	PORTD=0b11001010; 
							break;		}
		case 'T':   {	PORTD=0b00101010; 
							break;		}
	    case 'U':   {	PORTD=0b10101010; 
							break;		}
		case 'V':   {	PORTD=0b01101010; 
							break;		}
		case 'W':   {	PORTD=0b11101010; 
							break;		}
		case 'X': 	{	PORTD=0b00011010; 
							break;		}
		case 'Y':	{	PORTD=0b10011010; 
							break;		}
		case 'Z':	{	PORTD=0b01011010; 
							break;		}
		case '1':	{	PORTD=0b10001100; //1
							break;		}		
		case '2':	{	PORTD=0b01001100; //2
							break;		}				
		case '3':	{	PORTD=0b11001100; //3
							break;		}						
		case '4':   {	PORTD=0b00101100; //4
							break;		}						
		case '5':   {	PORTD=0b10101100; //5
							break;		}						
		case '6':	{	PORTD=0b01101100; //6
							break;		}					
		case '7':	{	PORTD=0b11101100; //7
							break;		}	
        case '8':	{	PORTD=0b00011100; //8
							break;		}							
		case '9':	{	PORTD=0b10011100; //9
							break;		}					
		case '0':	{	PORTD=0b00001100; //0
							break;		}							 
		case ':':	{	PORTD=0b01011100; //:
							break;		} 
		case ' ':	{	PORTD=0b00000100; //space
							break;		} 		 							
	    case 'd':	{	PORTD=0b00100110; //d
							break;		}
		case 'm':	{	PORTD=0b10110110; //m
							break;		}
		case 's':	{	PORTD=0b11001110; //s
							break;		}
		 }	
							
							_delay_ms(5);
							PORTC=0b00010000; //enable is low, with RS high
							_delay_ms(5);
							PORTC=0b00110000; //enable is high, with RS high (ready to send more data)
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