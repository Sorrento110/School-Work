#include "OneVoter.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'OneVoter' for the queueing theory computation.
 *
 * This is the data payload class for the data for a single voter.
 * 'sequenceNumber' is a unique number for each voter just to be
 *    able to follow the instance of the class
 * 'timeArrival' is the time the voter arrives
 * 'timeStartVoting' is the time the voter starts voting
 * 'timeVoteDuration' is the service of the voter actually voting
 * 'machineNumber' is the voting machine assigned to the voter
 * 'timeDoneVoting' is the time the voter actually finishes voting
 * 'timeWaiting' is the time spent waiting in line
 *
 * 'sequenceNumber', 'timeArrival', and 'timeVoteDuration' are parameters
 * passed to the constructor.
 *
 * 'timeStartVoting' and 'machineNumber' are generated in the simulation,
 * at which time we can compute 'timeWaiting' and 'timeDoneVoting'.
 *
 * Author: Duncan A. Buell
 * Date last modified: 20 April 2015
**/

/******************************************************************************
 * Constructor
**/
OneVoter::OneVoter()
{
  this->sequenceNumber = DUMMY;
  this->timeArrival = DUMMY;
  this->timeStartVoting = DUMMY;
  this->timeVoteDuration = DUMMY;  
  this->machineNumber = DUMMY;
  this->timeDoneVoting = DUMMY;
  this->timeWaiting = DUMMY;
}

/******************************************************************************
 * Constructor
**/
OneVoter::OneVoter(int sequence, int arrival, int duration)
{
  this->sequenceNumber = sequence;
  this->timeArrival = arrival;
  this->timeStartVoting = DUMMY;
  this->timeVoteDuration = duration;  
  this->machineNumber = DUMMY;
  this->timeDoneVoting = DUMMY;
  this->timeWaiting = DUMMY;
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
 * Accessor for 'machineNum'
**/
int OneVoter::getMachineNumber()
{
  return this->machineNumber;
}

/******************************************************************************
 * Accessor for 'sequenceNumber'
int OneVoter::getSequenceNumber()
{
  return this->sequenceNumber;
}
**/

/******************************************************************************
 * Accessor for 'timeArrival'
**/
int OneVoter::getTimeArrival()
{
  return this->timeArrival;
}

/******************************************************************************
 * Accessor for 'timeDoneVoting'
**/
int OneVoter::getTimeDoneVoting()
{
  return this->timeDoneVoting;
}

/******************************************************************************
 * Accessor for 'timeWaiting'
**/
int OneVoter::getTimeWaiting()
{
  return this->timeWaiting;
}

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'assignMachine' to assign this voter to a machine.
 *
 * At the time we assign a machine we can compute the waiting time and
 * the time the voter will be done voting.
 *
 * Parameters:
 *   machineNumber -- the number of the machine to assign to this voter
 *   startTime -- the time this voter starts voting
**/
void OneVoter::assignMachine(int machineNumber, int startTime)
{
  //By using 'this' we can be sure we are accessing variables in the scope of 
  //the function instead of accidentally accessing other variables.
  this->machineNumber = machineNumber;
  this->timeStartVoting = startTime;
  this->timeDoneVoting = this->timeStartVoting + this->timeVoteDuration;
  this->timeWaiting = this->timeStartVoting - this->timeArrival;
}

/******************************************************************************
 * Function 'doneVoting' to close out the record for this voter.
**/
void OneVoter::doneVoting()
{
  this->machineNumber = DUMMY;
}

/******************************************************************************
 * Function 'toString'.
 * This is the usual 'toString' to output the basic data of this class.
 *
 * Returns:
 *   the 'toString'
**/
string OneVoter::toString()
{
  string s = "";

  s += "seq#  mach# arr   start dur   done  wait"
       + Utils::Format(this->sequenceNumber, 5)
       + Utils::Format(this->machineNumber, 5)
       + Utils::Format(this->timeArrival, 5)
       + Utils::Format(this->timeStartVoting, 5)
       + Utils::Format(this->timeVoteDuration, 5)
       + Utils::Format(this->timeDoneVoting, 5)
       + Utils::Format(this->timeWaiting, 5);

  return s;
}
