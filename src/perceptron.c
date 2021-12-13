//========================================================//
//  perceptron.c                                            //
//  Source file for the Branch Predictor                  //
//														  //
// The following code is developed by 					  //
// Pulkit Agrawal.										  //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//
#include <stdio.h>
#include "perceptron.h"

//
//TODO: Add your extern variables defined in your 
//header file here.
//

//------------------------------------//
//      Predictor Data Structures     //
//------------------------------------//

uint32_t gHistoryEntry_perceptron;
uint32_t gHistoryBits_perceptron; // Number of bits used for Global History

int threshold_perceptron;
uint32_t perceptronTableAddressBits;
uint32_t numberOfPerceptronTableEntries;
uint32_t numberOfWeightsInPerceptronEntry;
int ** perceptronTable;

//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

// Initialize the predictor
//
void init_predictor_perceptron() {
	
	gHistoryEntry_perceptron = 0;
	threshold_perceptron = ( 1.93 * perceptronTableAddressBits ) + 14;
	numberOfPerceptronTableEntries = pow(2, perceptronTableAddressBits);
	numberOfWeightsInPerceptronEntry = gHistoryBits_perceptron;
	perceptronTable = (int **) malloc ( numberOfPerceptronTableEntries * sizeof(int *) );
	for (int i=0; i<numberOfPerceptronTableEntries; i++) {
		perceptronTable[i] = (int *) malloc ((numberOfWeightsInPerceptronEntry+1) * sizeof(int *));
		for (int j=0; j<numberOfWeightsInPerceptronEntry+1; j++){
			perceptronTable[i][j] = 1;
		}
	}
}

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction_perceptron(uint32_t pc) {
	
	int dotProductResult = dotProductCalc (pc);
	return (dotProductResult > 0)? TAKEN : NOTTAKEN;
	
}

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void train_predictor_perceptron(uint32_t pc, uint8_t outcome) {
	
	uint8_t predictedOutcome = make_prediction_perceptron(pc);
	uint32_t addressMask = ~(0xffffffff<<numberOfWeightsInPerceptronEntry);
	uint32_t index = pc&addressMask;
	int signT = (outcome == TAKEN)? 1 : -1;
	int dotProductResult = dotProductCalc(pc);
	if (outcome != predictedOutcome) {
		if (abs(dotProductResult)<threshold_perceptron) {
			for (int i=0; i<numberOfWeightsInPerceptronEntry; i++){
				if (gHistoryEntry_perceptron & (1<<i) == TAKEN){
					perceptronTable[index][i+1] = perceptronTable[index][i+1] + signT*(1);
				} else if (gHistoryEntry_perceptron & (1<<i) == NOTTAKEN){
					perceptronTable[index][i+1] = perceptronTable[index][i+1] + signT*(-1);
				}
				
			}
			perceptronTable[index][0] = perceptronTable[index][0] + signT;
		}
	}
	
	gHistoryEntry_perceptron = ((gHistoryEntry_perceptron<<1)|(uint32_t)outcome);
	
}

int dotProductCalc (uint32_t pc) {
	uint32_t addressMask = ~(0xffffffff<<numberOfWeightsInPerceptronEntry);
	uint32_t index = pc&addressMask;
	int result = perceptronTable[index][0];
	for (int i=0; i<numberOfWeightsInPerceptronEntry; i++) {
		if (gHistoryEntry_perceptron & (1<<i) == TAKEN){
			result += perceptronTable[index][i+1];
		} else if (gHistoryEntry_perceptron & (1<<i) == NOTTAKEN){
			result -= perceptronTable[index][i+1];
		} 
	}
	
	return result;
}
	