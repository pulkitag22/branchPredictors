//========================================================//
//  tournament.h                                            //
//  Header file for the Branch Predictor                  //
//														  //
// The following code is developed by 					  //
// Pulkit Agrawal.										  //
//                                                        //
//  Includes function prototypes and global predictor     //
//  variables and defines                                 //
//========================================================//

#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "defines.h"
#include <math.h>

// Definitions for 2-bit score counters
#define SP1  0			// predictor 1 performs better
#define WP1  1			// predictor 1 performs better
#define WP2  2			// predictor 2 performs better
#define SP2  3			// predictor 2 performs better

//TODO: add the two predictors you want to incorporate
// in this tournament predictor.
#include "gshare.h"
#include "pshare.h"

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//
//
//TODO: declare the variables as extern which will be 
// defined in your tournament.c file.
//

extern uint32_t tournamentScoreTableAddressBits;
extern uint32_t numberOfScoreCouters;
extern uint8_t * scoreCounters;

//------------------------------------//
//    Predictor Function Prototypes   //
//------------------------------------//

// Initialize the predictor
//
void init_predictor_tournament();

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction_tournament(uint32_t pc);

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void train_predictor_tournament(uint32_t pc, uint8_t outcome);

#endif
