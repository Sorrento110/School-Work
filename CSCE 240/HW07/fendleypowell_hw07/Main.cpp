#include "Main.h"

/*******************************************************************************
12345678901234567890123456789012345678901234567890123456789012345678901234567890
 * Main program for Homework 2.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Date: 31 December 2014
 *
**/

int main(int argc, char *argv[])
{
  int howManyMachinesLower = 0;
  int howManyMachinesUpper = 0;
  int howManyVoters = 0;
  int numberOfTimeSteps = 0;
  double voteTimeMean = 0.0;
  double voteTimeDev = 0.0;

  Queue queue;

  cin >> howManyVoters >> howManyMachinesLower >> howManyMachinesUpper
      >> numberOfTimeSteps >> voteTimeMean >> voteTimeDev;
  //This initialize could fail if one of the arguments passed to it was not of
  //the correct type, but we check this by storing the arguments in pre-set 
  //variable, and the program would die before they were passed into initialize.
  queue.initialize(howManyVoters, howManyMachinesLower, howManyMachinesUpper,
                   numberOfTimeSteps,
                   voteTimeMean, voteTimeDev);

  cout << "Voters: " << howManyVoters
       << ", timeSteps: " << numberOfTimeSteps
       << ", machines: " << howManyMachinesLower << " to " << howManyMachinesUpper
       << ", mean & dev vote times: " << voteTimeMean << " " << voteTimeDev
       << endl;
  //This would only crash or throw an error if there was something wrong with 
  //runSimulation.
  queue.runSimulation();

  return 0;
}

