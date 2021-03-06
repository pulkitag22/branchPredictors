//========================================================//
//  pshare.c                                              //
//  Source file for the Branch Predictor                  //
//														  //
// The following code is developed by 					  //
// Pulkit Agrawal.										  //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//

#include <stdio.h>
#include "pshare.h"

//------------------------------------//
//      Predictor Data Structures     //
//------------------------------------//

uint32_t pHistoryBits; // Number of bits used for Private History
uint32_t pHistoryTableAddressBits;
uint32_t numberPHistoryEntries;
uint32_t * pHistoryEntry;
uint32_t numberBinaryCounters_pshare;
uint8_t * sharedBinaryCounter_pshare;

//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

// Initialize the predictor
//
void init_predictor_pshare() {
	
	numberBinaryCounters_pshare = pow(2,pHistoryBits);
	sharedBinaryCounter_pshare = (uint8_t *)malloc(numberBinaryCounters_pshare*sizeof(uint8_t));

	numberPHistoryEntries = pow(2,pHistoryTableAddressBits);
	pHistoryEntry = (uint32_t *)malloc(numberPHistoryEntries*sizeof(uint32_t));
	
	for (int i=0; i<numberBinaryCounters_pshare; i++) {
		*(sharedBinaryCounter_pshare + i) = SN;
	}
	
	for (int i=0; i<numberPHistoryEntries; i++) {
		*(pHistoryEntry + i) = 0;
	}
  
}

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction_pshare(uint32_t pc) {
	
	uint32_t addressMaskTableEntry = ~(0xffffffff<<pHistoryTableAddressBits);
	uint32_t addressMaskSharedCounter = ~(0xffffffff<<pHistoryBits);
	uint32_t counterIndex = *(pHistoryEntry + (pc&addressMaskTableEntry));
	counterIndex = counterIndex & addressMaskSharedCounter;
	uint8_t outcome;

	switch(sharedBinaryCounter_pshare[counterIndex]) {
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
void train_predictor_pshare(uint32_t pc, uint8_t outcome) {
	
	uint32_t addressMaskTableEntry = ~(0xffffffff<<pHistoryTableAddressBits);
	uint32_t addressMaskSharedCounter = ~(0xffffffff<<pHistoryBits);
	uint32_t counterIndex = *(pHistoryEntry + (pc&addressMaskTableEntry));
	counterIndex = counterIndex & addressMaskSharedCounter;
	uint8_t predictedOutcome = make_prediction_pshare(pc);

	if (predictedOutcome == outcome){
		switch(sharedBinaryCounter_pshare[counterIndex]){
			case WN:
				sharedBinaryCounter_pshare[counterIndex] = SN;
				break;
			case WT:
				sharedBinaryCounter_pshare[counterIndex] = ST;
				break;
			default:
				// If there is not a compatable state in the counter then return NOTTAKEN
				break;	
		}  
	} else {
		switch(sharedBinaryCounter_pshare[counterIndex]){
			case SN:
				sharedBinaryCounter_pshare[counterIndex] = WN;
				break;
			case WN:
				sharedBinaryCounter_pshare[counterIndex] = WT;
				break;
			case WT:
				sharedBinaryCounter_pshare[counterIndex] = WN;
				break;
			case ST:
				sharedBinaryCounter_pshare[counterIndex] = WT;
				break;
			default:
				// If there is not a compatable state in the counter then return NOTTAKEN
				break;	
		}	  
	}
	
	pHistoryEntry[pc&addressMaskTableEntry] = (pHistoryEntry[pc&addressMaskTableEntry]<<1) | (uint32_t)outcome;
  
}
