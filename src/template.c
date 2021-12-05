//========================================================//
//  template.c                                            //
//  Source file for the Branch Predictor                  //
//														  //
// The following code is developed by 					  //
// Pulkit Agrawal.										  //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//
#include <stdio.h>
#include "template.h"

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


//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

// Initialize the predictor
//
void init_predictor_template()
{
  //
  //TODO: Initialize Branch Predictor Data Structures
  //
}

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction_template(uint32_t pc)
{
  //
  //TODO: Implement prediction scheme
  //
}

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void train_predictor_template(uint32_t pc, uint8_t outcome)
{
  //
  //TODO: Implement Predictor training
  //
}
