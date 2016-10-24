/****************************************************************
 * Header file for the class 'OneVoter' for the queueing
 * theory program.
 *
 * Author/copyright:  Duncan Buell
 * Date: 31 December 2014
 *
**/

#ifndef ONEVOTER_H
#define ONEVOTER_H

#define DUMMY -99

#include <iostream>
#include <random>
using namespace std;

#include "../../Utilities/Utils.h" // used for formatting

#include "MyRandom.h"

class OneVoter
{
public:
  OneVoter();
  OneVoter(int sequence, int arrival, int duration);
  virtual ~OneVoter();

  int getMachineNumber();
  int getSequenceNumber();
  int getTimeArrival();
  int getTimeDoneVoting();
  int getTimeStartVoting();
  int getTimeVoteDuration();
  int getTimeWaiting();

  void assignMachine(int machineNumber, int startTime);
  void doneVoting();

  string toString();

private:
  int machineNumber;
  int sequenceNumber;
  int timeArrival;
  int timeDoneVoting;
  int timeStartVoting;
  int timeVoteDuration;
  int timeWaiting;
};

#endif
