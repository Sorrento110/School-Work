#include "OneVoter.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'OneVoter' for the queueing theory computation.
 *
 * This is a data payload for the variables of the class. There is nothing
 * here except for accessors and a 'toString', except for two functions that:
 *   assign a machine, start time, etc., to the instance
 *   assign a dummy ending machine number to a voter done voting 
 *
 * Author: Powell Fendley
 * Date last modified: 9 April 2015
**/
//Initialize all variables:
int machineNumber;
int sequenceNumber;
int timeArrival;
int timeDoneVoting;
int timeStartVoting;
int timeVoteDuration;
int timeWaiting;

/******************************************************************************
 * Constructor
**/
OneVoter::OneVoter()
{
  sequenceNumber=0;
  timeArrival=0;
  timeVoteDuration=0;
  timeDoneVoting=0;
}

/******************************************************************************
 * Constructor
**/
OneVoter::OneVoter(int sequence, int arrival, int duration)
{
  sequenceNumber=sequence;
  timeArrival=arrival;
  timeVoteDuration=duration;
  timeDoneVoting=0;
}

/******************************************************************************
 * Destructor
**/
OneVoter::~OneVoter()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * Accessor for 'machineNumber'
**/
int OneVoter::getMachineNumber()
{
  return machineNumber;
}

/******************************************************************************
 * Accessor for 'sequenceNumber'
**/
int OneVoter::getSequenceNumber()
{
  return sequenceNumber;
}


/******************************************************************************
 * Accessor for 'timeArrival'
**/
int OneVoter::getTimeArrival()
{
  return timeArrival;
}

/******************************************************************************
 * Accessor for 'timeDoneVoting'
**/
int OneVoter::getTimeDoneVoting()
{
return timeDoneVoting;
}

/******************************************************************************
 * Accessor for 'timeStartVoting'
**/
int OneVoter::getTimeStartVoting()
{
  return timeStartVoting;
}

/******************************************************************************
 * Accessor for 'timeVoteDuration'
**/
int OneVoter::getTimeVoteDuration()
{
  return timeVoteDuration;
}


/******************************************************************************
 * Accessor for 'timeWaiting'
**/
int OneVoter::getTimeWaiting()
{
return timeWaiting;
}

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'assignMachine' 
**/
void OneVoter::assignMachine(int machineNumber, int startTime)
{
  machineNumber=machineNumber;
  timeStartVoting=startTime;
  timeWaiting= timeStartVoting-timeArrival;
}

/******************************************************************************
 * Function 'doneVoting' 
**/
void OneVoter::doneVoting()
{
  timeDoneVoting=timeStartVoting+timeVoteDuration;
}

/******************************************************************************
 * Function 'toString'.
**/
string OneVoter::toString()
{
  string s = "";

  return s;
}
