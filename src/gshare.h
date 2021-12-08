//========================================================//
//  gshare.h                                              //
//  Header file for the Branch Predictor                  //
//														  //
// The following code is developed by 					  //
// Pulkit Agrawal.										  //
//                                                        //
//  Includes function prototypes and global predictor     //
//  variables and defines                                 //
//========================================================//

#ifndef GSHARE_H
#define GSHARE_H

#include "defines.h"
#include <math.h>

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//
extern uint32_t gHistoryEntry;
extern uint32_t gHistoryBits; // Number of bits used for Global History
extern uint32_t numberBinaryCounters_gshare;
extern uint8_t * sharedBinaryCounter_gshare;

//------------------------------------//
//    Predictor Function Prototypes   //
//------------------------------------//

// Initialize the predictor
//
void init_predictor_gshare();

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction_gshare(uint32_t pc);

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void train_predictor_gshare(uint32_t pc, uint8_t outcome);

#endif
