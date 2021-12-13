//========================================================//
//  perceptron.h                                            //
//  Header file for the Branch Predictor                  //
//														  //
// The following code is developed by 					  //
// Pulkit Agrawal.										  //
//                                                        //
//  Includes function prototypes and global predictor     //
//  variables and defines                                 //
//========================================================//

#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "defines.h"
#include <math.h>

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//

extern uint32_t gHistoryEntry_perceptron;
extern uint32_t gHistoryBits_perceptron; // Number of bits used for Global History

extern int threshold_perceptron;
extern uint32_t perceptronTableAddressBits;
extern uint32_t numberOfPerceptronTableEntries;
extern uint32_t numberOfWeightsInPerceptronEntry;
extern int ** perceptronTable;

//------------------------------------//
//    Predictor Function Prototypes   //
//------------------------------------//

// Initialize the predictor
//
void init_predictor_perceptron();

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction_perceptron(uint32_t pc);

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void train_predictor_perceptron(uint32_t pc, uint8_t outcome);

int dotProductCalc (uint32_t pc);

#endif
