/*
 * myLCD.h
 *
 * Created: 27/05/2015 8:30:32 pm
 *  Author: Tauseef (u4858965)
 */ 


#ifndef MYLCD_H_
#define MYLCD_H_


void clearLCD() {
	
	DDRC=0b00110000; //portc has RS on bit 4, and enable on bit 5
	DDRD=0xFF;
	_delay_ms(200); //wait a little bit of time for the LCD to power up properly.
	
	//initialization of LCD screen
	
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
	
	//_delay_ms(100); //wait a little longer after initialisation (may not be required, but it seems to help)
	
	//now i am going to enter a real character
	PORTC=0b00110000; //enable is high, with RS high (I'm going to send data)
	_delay_ms(5);
	

}

void print( char letter ) {
	
	_delay_ms(5);
	
	PORTC=0b00110000;
	
	//enable is high, with RS high (I'm going to send data)
	_delay_ms(5);
	
	switch(letter) {
		
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
		case '1':	{	PORTD=0b10001100; 
							break;		}		
		case '2':	{	PORTD=0b01001100; 
							break;		}				
		case '3':	{	PORTD=0b11001100; 
							break;		}						
		case '4':   {	PORTD=0b00101100; 
							break;		}						
		case '5':   {	PORTD=0b10101100; 
							break;		}						
		case '6':	{	PORTD=0b01101100; 
							break;		}					
		case '7':	{	PORTD=0b11101100; 
							break;		}	
        case '8':	{	PORTD=0b00011100; 
							break;		}							
		case '9':	{	PORTD=0b10011100; 
							break;		}					
		case '0':	{	PORTD=0b00001100; 
							break;		}							 
		case ':':	{	PORTD=0b01011100; 
							break;		} 
		case ' ':	{	PORTD=0b00000100; 
							break;		} 		 							
		case '.':	{	PORTD=0b01110100; 
							break;		}
		 }	
							
		_delay_ms(5);
		PORTC=0b00010000; //enable is low, with RS high
		_delay_ms(5);
		PORTC=0b00110000; //enable is high, with RS high (ready to send more data)
 
 }	


void moveToNextLine () { // move to next line on the LCD
	
	_delay_ms(5);
	PORTC=0b00100000;
	_delay_ms(5);
	PORTD=0b00000011;
	_delay_ms(5);
	PORTC=0b00000000;
	
}




#endif /* MYLCD_H_ */