//========================================================//
//  pshare.h                                              //
//  Header file for the Branch Predictor                  //
//														  //
// The following code is developed by 					  //
// Pulkit Agrawal.										  //
//                                                        //
//  Includes function prototypes and global predictor     //
//  variables and defines                                 //
//========================================================//

#ifndef PSHARE_H
#define PSHARE_H

#include "defines.h"
#include <math.h>

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//
extern uint32_t pHistoryBits; // Number of bits used for Private History
extern uint32_t pHistoryTableAddressBits;
extern uint32_t numberPHistoryEntries;
extern uint32_t * pHistoryEntry;
extern uint32_t numberBinaryCounters;
extern uint8_t * sharedBinaryCounter;
//------------------------------------//
//    Predictor Function Prototypes   //
//------------------------------------//

// Initialize the predictor
//
void init_predictor_pshare();

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction_pshare(uint32_t pc);

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void train_predictor_pshare(uint32_t pc, uint8_t outcome);

#endif
