
#ifndef MNNCALCULATOR_H_
#define MNNCALCULATOR_H_

volatile static unsigned int MNN = 0;
volatile unsigned int MNNinDigits[4];


void printMNN () {
	
	// this function will calculate and print MNN
	
	if (calculateMNN==true) { 
		
		int i = 1;
	 //  "i" starts from 1, because I am excluding the time it took to get the first beat
		
		for (i = 1; i < indexOfTimeIntervalVector; i++) {
			
			sumOFTimeIntervalsForAllBeatsInLastFourSeconds += timeIntervalForAllBeats[i];
			
		}
		
		MNN = sumOFTimeIntervalsForAllBeatsInLastFourSeconds/(heartBeatTrackerForMNN-1); // MNN will be calculated every 15 seconds
		
		sumOFTimeIntervalsForAllBeatsInLastFourSeconds = 0;
		
		heartBeatTrackerForMNN = 0;
		calculateMNN = false;  
		calculateSDNN = true;
		
	}
	
	// the LCD displays data bit by bit. So I am separating the decimal value to 3 bits.
	
	MNNinDigits[0] = (MNN%10)+'0'; // Print function takes input char. So i am adding zero to "int" in order to convert the value to char.
	MNNinDigits[1] = ((MNN%100-MNN%10)/10)+'0';
	MNNinDigits[2] = ((MNN%1000-MNN%100)/100)+'0';
	MNNinDigits[3] = ((MNN%10000-MNN%1000)/1000)+'0';
	
	print('M');
	print('N');
	print('N');
	
	print(MNNinDigits[3]);
	print('.');
	print(MNNinDigits[2]);
	print(MNNinDigits[1]);
	print(MNNinDigits[0]);
	
	
}


#endif /* MNNCALCULATOR_H_ */