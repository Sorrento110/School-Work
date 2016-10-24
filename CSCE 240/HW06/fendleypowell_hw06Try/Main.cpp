#include "Main.h"

/*******************************************************************************
12345678901234567890123456789012345678901234567890123456789012345678901234567890
 * Main program for Homework 2.
 *
 * This program sets up and runs a queueing model simulation of an election.
 * The program creates an instance of 'Queue', initializes the instance from 
 * an input file, echoes the input, and then runs the simulation.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Date: 23 March 2015
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

  // input the data, with no bulletproofing
  cin >> howManyVoters >> howManyMachinesLower >> howManyMachinesUpper
      >> numberOfTimeSteps >> voteTimeMean >> voteTimeDev;

  queue.initialize(howManyVoters, howManyMachinesLower, howManyMachinesUpper,
                   numberOfTimeSteps,
                   voteTimeMean, voteTimeDev);

  cout << "Voters: " << howManyVoters
       << ", timeSteps: " << numberOfTimeSteps
       << ", machines: " << howManyMachinesLower << " to " << howManyMachinesUpper
       << ", mean & dev vote times: " << voteTimeMean << " " << voteTimeDev
       << endl;
  
  cout << "We made it to run sim!";
  queue.runSimulation();


  return 0;
}

