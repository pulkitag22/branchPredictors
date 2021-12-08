//========================================================//
//  predictor.c                                           //
//  Source file for the Branch Predictor                  //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//
#include <stdio.h>
#include "predictor.h"

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//

// Handy Global for use in output routines
const char *bpName[5] = { "Static", "Gshare", "Pshare",
                          "Tournament", "Custom" };

int bpType;       // Branch Prediction Type
int verbose;

//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

// Initialize the predictor
//
void init_predictor() {
	
	// Initialize a prediction based on the bpType
	switch (bpType) {
		case STATIC:
			break;
		case GSHARE:
			init_predictor_gshare();
			break;
		case PSHARE:
			init_predictor_pshare();
			break;
		case TOURNAMENT:
		init_predictor_tournament();
			break;
		case CUSTOM:
			break;
		default:
			break;
	}
}

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction(uint32_t pc) {
	
	uint8_t outcome = NOTTAKEN;
	
	// Make a prediction based on the bpType
	switch (bpType) {
		case STATIC:
			outcome = TAKEN;
			break;
		case GSHARE:
			outcome = make_prediction_gshare(pc);
			break;
		case PSHARE:
			outcome = make_prediction_pshare(pc);
			break;
		case TOURNAMENT:
			outcome = make_prediction_tournament(pc);
			break;
		case CUSTOM:
		default:
			// If there is not a compatable bpType then return NOTTAKEN
			outcome = NOTTAKEN;
			break;
	}
	
	return outcome;
}

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void train_predictor(uint32_t pc, uint8_t outcome)
{
  // Train a prediction based on the bpType
	switch (bpType) {
		case STATIC:
			break;
		case GSHARE:
			train_predictor_gshare(pc, outcome);
			break;
		case PSHARE:
			train_predictor_pshare(pc, outcome);
			break;
		case TOURNAMENT:
			train_predictor_tournament(pc, outcome);
			break;
		case CUSTOM:
		default:
			// If there is not a compatable bpType then return NOTTAKEN
			outcome = NOTTAKEN;
			break;
	}
	
}
