
#ifndef SDNNCALCULATOR_H_
#define SDNNCALCULATOR_H_

volatile unsigned int SDNNinDigits[4];
volatile static unsigned int SDNN = 0;
volatile static unsigned int sumOfTimeIntervals = 0;
volatile static unsigned int variance = 0;


void printSDNN () {
	
	// this function will calculate and print SDNN every 4 seconds 
		
	int i, diff, sq =0;
	
	if (calculateSDNN==true) {
		
		for (i = 0; i < indexOfTimeIntervalVector; i++) {
			
			diff = (timeIntervalForAllBeats[i] - MNN);
			
			sq += (diff*diff); // = (diff)^2
			
		}
		
		variance = sq/(indexOfTimeIntervalVector-1);
		
		SDNN = sqrt(variance);
		
		indexOfTimeIntervalVector = 0;
		
		calculateSDNN = false;
		
	}
	
	// the LCD displays data bit by bit. So I am separating the decimal value to 3 bits.
	
	SDNNinDigits[0] = (SDNN%10)+'0'; // Print function takes input char. So i am adding zero to "int" in order to convert the value to char.
	SDNNinDigits[1] = ((SDNN%100-SDNN%10)/10)+'0';
	SDNNinDigits[2] = ((SDNN%1000-SDNN%100)/100)+'0';
	SDNNinDigits[3] = ((SDNN%10000-SDNN%1000)/1000)+'0';
	
	print(' '); // space
	print('S');
	print('D');
	
	print(SDNNinDigits[3]);
	print('.');
	print(SDNNinDigits[2]);
	print(SDNNinDigits[1]);
	print(SDNNinDigits[0]);

}



#endif /* SDNNCALCULATOR_H_ */