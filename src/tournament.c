//========================================================//
//  tournamment.c                                         //
//  Source file for the Branch Predictor                  //
//														  //
// The following code is developed by                     //
// Pulkit Agrawal.                                        //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//
#include <stdio.h>
#include "tournamment.h"

//
//TODO: Add your extern variables defined in your 
//header file here.
//

//------------------------------------//
//      Predictor Data Structures     //
//------------------------------------//

//
//TODO: Add your own Branch Predictor data structures here
//
uint32_t tournamentScoreTableAddressBits;
uint32_t numberOfScoreCouters;
uint8_t * scoreCounters;

//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

// Initialize the predictor
//
void init_predictor_tournament() {
	//
	//TODO: Initialize Branch Predictor Data Structures
	//
	
	numberOfScoreCouters = pow(2,tournamentScoreTableAddressBits);
	scoreCounters = (uint8_t *) malloc (numberOfScoreCouters * sizeof(uint8_t));
	
	for (int i=0; i<numberOfScoreCouters; i++){
		*(scoreCounters + i) = SP1;
	}
	
	//predictor 1 init 
	init_predictor_gshare();
	
	//predictor 2 init 
	init_predictor_pshare();
	
	
}

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction_tournament(uint32_t pc) {
	//
	//TODO: Implement prediction scheme
	//
	
	uint32_t addressMaskScoreEntry = ~(0xffffffff<<tournamentScoreTableAddressBits);
	uint8_t counterValue = *(scoreCounters + (pc&addressMaskScoreEntry));
	uint8_t outcome_p1 = make_prediction_gshare(pc);
	uint8_t outcome_p2 = make_prediction_pshare(pc);	
	uint8_t outcome;
	
	if (counterValue > 1) {
		outcome = outcome_p2;
	} else if (counterValue < 2) {
		outcome = outcome_p1;
	}
	
	return outcome;
}

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void train_predictor_tournament(uint32_t pc, uint8_t outcome) {
	//
	//TODO: Implement Predictor training
	//
	
	uint32_t addressMaskScoreEntry = ~(0xffffffff<<tournamentScoreTableAddressBits);
	uint8_t counterValue = *(scoreCounters + (pc&addressMaskScoreEntry));
	uint8_t outcome_p1 = make_prediction_gshare(pc);
	uint8_t outcome_p2 = make_prediction_pshare(pc);
	
	if (outcome_p1 == outcome_p2) {
		return;
	} else if (outcome_p1 != outcome_p2) {
		if ( (outcome_p1 == outcome) && (counterValue>0) ) {
			scoreCounters[pc&addressMaskScoreEntry]--;
		} else if ( (outcome_p2 == outcome) && (counterValue<3) ) {
			scoreCounters[pc&addressMaskScoreEntry]++;
		}
	}
	
}
