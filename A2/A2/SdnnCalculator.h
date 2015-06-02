/*
 * SdnnCalculator.h
 *
 * Created: 3/06/2015 1:26:53 am
 *  Author: Tanzim
 */ 


#ifndef SDNNCALCULATOR_H_
#define SDNNCALCULATOR_H_


// this function will calculate and print SDNN


void printSDNN () {
	
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
	
	SDNNinDigits[0] = (SDNN%10)+'0';
	SDNNinDigits[1] = ((SDNN%100-SDNN%10)/10)+'0';
	SDNNinDigits[2] = ((SDNN%1000-SDNN%100)/100)+'0';
	SDNNinDigits[3] = ((SDNN%10000-SDNN%1000)/1000)+'0';
	
	print(' ');
	print('S');
	print('D');
	
	print(SDNNinDigits[3]);
	print('.');
	print(SDNNinDigits[2]);
	print(SDNNinDigits[1]);
	print(SDNNinDigits[0]);

}



#endif /* SDNNCALCULATOR_H_ */