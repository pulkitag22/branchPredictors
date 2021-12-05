//========================================================//
//  template.h                                            //
//  Header file for the Branch Predictor                  //
//														  //
// The following code is developed by 					  //
// Pulkit Agrawal.										  //
//                                                        //
//  Includes function prototypes and global predictor     //
//  variables and defines                                 //
//========================================================//

#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "defines.h"

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//
//
//TODO: declare the variables as extern which will be 
// defined in your template.c file.
//

//------------------------------------//
//    Predictor Function Prototypes   //
//------------------------------------//

// Initialize the predictor
//
void init_predictor_template();

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction_template(uint32_t pc);

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void train_predictor_template(uint32_t pc, uint8_t outcome);

#endif
