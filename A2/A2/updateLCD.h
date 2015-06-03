/*
 * updateLCD.h
 *
 * Created: 27/05/2015 9:19:17 pm
 *  Author: Tauseef (u4858965)
 */ 


#ifndef updateLCD_H_
#define updateLCD_H_
#include "heartBeatDetector.h"

#include "MNNCalculator.h"
#include "SdnnCalculator.h"


void updateLCD () { // this function will be used to update the LCD when new data is available for number of beats, HR, MNN, SDNN and time

		clearLCD(); // this function is from myLCD.h

		printTimeElapsed(); // this function is from updateLCD.h

		printNumberOfBeats(); // this function is from heartBeatDetector.h

		printHeartRate(); // this function is from heartBeatDetector.h

		moveToNextLine(); // this function is from myLCD.h

		printMNN(); // this function is from MNNCalculator.h

		printSDNN(); // this function is from SdnnCalculator.h

}



#endif /* updateLCD_H_ */