//========================================================//
//  gshare.c                                              //
//  Source file for the Branch Predictor                  //
//														  //
// The following code is developed by 					  //
// Pulkit Agrawal.										  //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//
#include <stdio.h>
#include "gshare.h"

//------------------------------------//
//      Predictor Data Structures     //
//------------------------------------//

uint32_t gHistoryBits; // Number of bits used for Global History
uint32_t gHistoryEntry;
uint32_t numberBinaryCounters_gshare;
uint8_t * sharedBinaryCounter_gshare;

//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

// Initialize the predictor
//
void init_predictor_gshare() {
	
	numberBinaryCounters_gshare = pow(2,gHistoryBits);
	sharedBinaryCounter_gshare = (uint8_t *)malloc(numberBinaryCounters_gshare*sizeof(uint8_t));

	gHistoryEntry = 0;
	for (int i=0; i<numberBinaryCounters_gshare; i++) {
		*(sharedBinaryCounter_gshare + i) = SN;
	}
  
}

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction_gshare(uint32_t pc) {
	
	uint32_t addressMask = ~(0xffffffff<<gHistoryBits);
	uint32_t counterIndex = (gHistoryEntry&addressMask)^(pc&addressMask);
	uint8_t outcome;

	switch(sharedBinaryCounter_gshare[counterIndex]) {
		case SN:
			outcome = NOTTAKEN;
			break;
		case WN:
			outcome = NOTTAKEN;
			break;
		case WT:
			outcome = TAKEN;
			break;
		case ST:
			outcome = TAKEN;
			break;
		default:
			// If there is not a compatable state in the counter then return NOTTAKEN
			outcome = NOTTAKEN;
			break;
	}

	return outcome;
  
}

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void train_predictor_gshare(uint32_t pc, uint8_t outcome) {
	
	uint32_t addressMask = ~(0xffffffff<<gHistoryBits);
	uint32_t counterIndex = (gHistoryEntry&addressMask)^(pc&addressMask);
	uint8_t predictedOutcome = make_prediction_gshare(pc);

	if (predictedOutcome == outcome){
		switch(sharedBinaryCounter_gshare[counterIndex]){
			case WN:
				sharedBinaryCounter_gshare[counterIndex] = SN;
				break;
			case WT:
				sharedBinaryCounter_gshare[counterIndex] = ST;
				break;
			default:
				// If there is not a compatable state in the counter then return NOTTAKEN
				break;	
		}  
	} else {
		switch(sharedBinaryCounter_gshare[counterIndex]){
			case SN:
				sharedBinaryCounter_gshare[counterIndex] = WN;
				break;
			case WN:
				sharedBinaryCounter_gshare[counterIndex] = WT;
				break;
			case WT:
				sharedBinaryCounter_gshare[counterIndex] = WN;
				break;
			case ST:
				sharedBinaryCounter_gshare[counterIndex] = WT;
				break;
			default:
				// If there is not a compatable state in the counter then return NOTTAKEN
				break;	
		}	  
	}
	
	gHistoryEntry = ((gHistoryEntry<<1)|sharedBinaryCounter_gshare[counterIndex]);
  
}
