/*
 * MNNCalculator.h
 *
 * Created: 3/06/2015 1:23:47 am
 *  Author: Tanzim
 */ 


#ifndef MNNCALCULATOR_H_
#define MNNCALCULATOR_H_

void printMNN () {
	
	if (calculateMNN==true) {
		
		int i = 1;
		// i will start from 1, because I am excluding the time it took to get the first beat
		
		for (i = 1; i < indexOfTimeIntervalVector; i++) {
			
			sumOFTimeIntervalsForAllBeatsInLastFourSeconds += timeIntervalForAllBeats[i];
			
		}
		
		MNN = sumOFTimeIntervalsForAllBeatsInLastFourSeconds/(heartBeatTrackerForMNN-1); // MNN will be calculated every 15 seconds
		
		sumOFTimeIntervalsForAllBeatsInLastFourSeconds = 0;
		
		heartBeatTrackerForMNN = 0;
		calculateMNN = false;
		calculateSDNN = true;
	}
	
	MNNinDigits[0] = (MNN%10)+'0';
	MNNinDigits[1] = ((MNN%100-MNN%10)/10)+'0';
	MNNinDigits[2] = ((MNN%1000-MNN%100)/100)+'0';
	MNNinDigits[3] = ((MNN%10000-MNN%1000)/1000)+'0';
	
	print('M');
	print('N');
	print('N');
	//display(':');
	
	print(MNNinDigits[3]);
	print('.');
	print(MNNinDigits[2]);
	print(MNNinDigits[1]);
	print(MNNinDigits[0]);
	
	
}







#endif /* MNNCALCULATOR_H_ */