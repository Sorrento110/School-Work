#include "Queue.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Queue' for the queueing theory computation.
 *
 * In this simulation we initialize the entire map of voters at the beginning
 * rather than generate them on the fly. We generate uniformly distributed
 * arrival times and normally distrubuted service times.
 *
 * The outer loop of the simulation allows a range of numbers of machines
 * to be simulated and then calls an inner function to do the simulation
 * for that many machines. The details of the inner function are part of
 * the documentation at that particular location in the code.
 *
 * We have two housekeeping functions to run at the end of the simulation
 * to compute the mean and std dev of the wait times and to plot a
 * histogram of the wait times.
 *
 * Author: Duncan A. Buell
 * Date last modified: 20 April 2015
**/

/******************************************************************************
 * Constructor
**/
Queue::Queue()
{
  cout << "Default constructor" << endl;
}

/******************************************************************************
 * Destructor
**/
Queue::~Queue()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/
/******************************************************************************
 * Function 'computeMeanAndDev'.
 * This computes the mean and standard deviation of the 'votersDoneVoting'
 * wait times.
 *
 * We compute the mean as mean = sum(wait_time) / number_of_voters
 * and then we compute the deviation as
 *   dev = sqrt(sum(wait_time - mean) / number_of_voters)
 *
 * These values are returned as pass-by-reference parameters of the function.
 *
 * Parameters:
 *   mean - the mean
 *   dev - the standard deviation
**/
void Queue::computeMeanAndDev(double& mean, double& dev)
{
  int sumOfWaitTimes = 0;
  double sumOfAdjustedTimes = 0.0;
  cout << "enter computeMeanAndDev" << endl;

  sumOfWaitTimes = 0;
  multimap<int, OneVoter>::iterator iterMultimap;
  //This loop could crash if the limits were set wrong, but by using 'this' 
  //and a container iterator, we can make sure it will not run farther 
  //than it needs to.
  for (iterMultimap = this->votersDoneVoting.begin();
       iterMultimap != this->votersDoneVoting.end(); ++iterMultimap)
  {
	//By using multimap iterators we can be sure we access the right data.
    OneVoter voter = iterMultimap->second;
    sumOfWaitTimes += voter.getTimeWaiting();
  }
  mean = static_cast<double>(sumOfWaitTimes)/
                   static_cast<double>(this->howManyVoters);

  sumOfAdjustedTimes = 0.0;
  //This loop runs for the same reason as above, because we are using a
  //container iterator to keep track of the loop's life.
  for (iterMultimap = this->votersDoneVoting.begin();
       iterMultimap != this->votersDoneVoting.end(); ++iterMultimap)
  {
    OneVoter voter = iterMultimap->second;
	//This initialization will work because every time the loop repeats
	//'thisAddin' will be cleaned and re-made.
    double thisAddin = static_cast<double>(voter.getTimeWaiting()) - mean;

    sumOfAdjustedTimes += (thisAddin) * (thisAddin);
  }
  dev = sqrt(sumOfAdjustedTimes/static_cast<double>(this->howManyVoters));

  cout << "leave computeMeanAndDev" << endl;
}

/******************************************************************************
 * Function 'doStatistics'.
 * This does stats on the voter queue 'votersDoneVoting'.
 *
 * We plot a histogram of the wait times and we compute the mean and deviation
 * of the wait times from that voter queue.
**/
void Queue::doStatistics()
{
  double mean;
  double dev;
  map<int, int> waitTimeMap;

  cout << "enter doStatistics" << endl;

  multimap<int, OneVoter>::iterator iterMultimap;
  //Once again we use iterators and 'this' to make sure the loop doesn't break
  for (iterMultimap = this->votersDoneVoting.begin();
       iterMultimap != this->votersDoneVoting.end(); ++iterMultimap)
  {
    OneVoter voter = iterMultimap->second;
    int waitTime = voter.getTimeWaiting();
    waitTimeMap[waitTime] = waitTimeMap[waitTime] + 1;
  }

  int timeLower = (waitTimeMap.begin())->first;
  int timeUpper = (waitTimeMap.rbegin())->first;
  //By setting timeUpper equal to the end of the map 'waitTimeMap' we can be sure
  //that the loop won't try to access anything over what the map has stored.
  for (int time = timeLower; time <= timeUpper; ++time)
  {
    int count = waitTimeMap[time];
    cout << Utils::Format(time, 6) << ": "
         << Utils::Format(count, 6) << ": ";
    cout << string(count, '*') << endl;
  }
  cout << endl << endl;

  computeMeanAndDev(mean, dev);
  cout << "mean and deviation of wait time are " << mean << ", " << dev << endl;
  //By clearing the waitTimeMap here we make sure no data will pollute the function 
  //if we call it again.
  waitTimeMap.clear();

  cout << "leave doStatistics" << endl;
}

/******************************************************************************
 * Function 'initialize'.
 * This initializes the voter queue.
 *
 * Note that the number of time steps is the minimum number of time steps to 
 * simulate. It is possible we simulate more because we keep going until the
 * queue of pending voters is totally drained.
 *
 * We load the voters into a backup 'multimap' that we copy with each
 * simulation to the 'multimap' that the simulation will use.
 *
 * Parameters:
 *   howManyVoters - the number of voters to simulate
 *   howManyMachinesLower - the lower bound of machines
 *   howManyMachinesUpper - the upper bound (inclusive) of machines
 *   numberOfTimeSteps - the number of time steps to simulate
 *   voteTimeMean - the mean of the voting time
 *   voteTimeDev - the deviation of the voting time
**/
void Queue::initialize(int howManyVoters,
                       int howManyMachinesLower, int howManyMachinesUpper,
                       int numberOfTimeSteps,
                       double voteTimeMean, double voteTimeDev)
{
  cout << "enter initialize" << endl;

  assert(howManyMachinesLower <= howManyMachinesUpper);
  this->howManyMachinesLower = howManyMachinesLower;
  this->howManyMachinesUpper = howManyMachinesUpper;

  this->howManyVoters = howManyVoters;
  //The way this loop is written will make sure that the program will not store
  //too many voters into the votersBackup multimap by comparing it to the 
  //maximum allowed number of voters passed in from main.
  for (int i = 0; i < this->howManyVoters; ++i)
  {
    int arrival = this->random.randomUniformInt(0, numberOfTimeSteps);
    int duration = int(this->random.randomNormal(voteTimeMean, voteTimeDev));
    OneVoter oneVoter(i, arrival, duration);
    this->votersBackup.insert(std::pair<int, OneVoter>(arrival, oneVoter));
  }

  cout << "leave initialize" << endl;
}

/******************************************************************************
 * Function 'runSimulation'.
 *
 * This is the function that runs the actual simulation. In this function
 * we run a loop on the number of machines and call an inner simulation
 * function to do the simulation for that many machines.
**/
void Queue::runSimulation()
{
  cout << "enter runSimulation" << endl;
  //This loop allows for the program to be run for a certain number of
  //machines. The numbers of machines are passed in from main, which
  //allows for no error to be made in this loop incrementation.
  for (int machineCount = this->howManyMachinesLower;
           machineCount <= this->howManyMachinesUpper; ++machineCount) 
  {
    cout << "run simulation for " << machineCount << " machines" << endl;

    // clear the vector of free machines
    // then load the vector, because all the machines are free
    this->freeMachines.clear();
	//This will work because machineCount is passed in from main.
    for (int i = 0; i < machineCount; ++i)
    {
      this->freeMachines.push_back(i);
    }

    // initialize or clear the three 'multimap' structures
	//Both of these are from the same type, and the equals operator is 
	//overridden in the multimap class, allowing for this to be used to 
	//copy votersBackup into votersPending.
    this->votersPending = this->votersBackup;
	//These clears make sure no pollution is carried over from a previous
	//iteration of the runSimulation into these lists.
    this->votersVoting.clear();
    this->votersDoneVoting.clear();

    runSimulation2(machineCount);

    this->doStatistics();
  }
  cout << "leave runSimulation" << endl;
}

/******************************************************************************
 * Function 'runSimulation2'.
 *
 * Loop on time if there are voters pending or in the process of voting.
 *
 *   Run an inner loop on 'thingsToDoThisTick' because there could be
 *   more than one event to process in a given time step.
 *     If there is a voter finishing this time step
 *       Take back the machine and push it on the 'freeMachines' 'vector'
 *       Erase the voter from the 'votersVoting' 'multimap'
 *       Add the voter to the 'votersDoneVoting' 'multimap'
 *       (Note that we actually create a new local 'OneVoter' instance
 *       so we can erase and add in either order.)
 *
 *     If there is a free machine 
 *       Take the top voter off the pending list and assign to that machine 
 *       (Again, we use a local variable so we can erase and add in either
 *       order.)
 *
 * Parameter:
 *   howManyMachines -- the number of machines to use in this simulation
**/
void Queue::runSimulation2(int howManyMachines)
{
  int time = 0;

  cout << "enter runSimulation2 for machine count: "
       << Utils::Format(howManyMachines, 5) << endl;
  cout << this->toString() << endl;
  
  time = 0;
  //This will run the loop when votersPending is not empty and when votersVoting is
  //not empty, allowing for all the voters to be processed and none that don't 
  //exist to be processed.
  while ((this->votersPending.size() > 0) || (this->votersVoting.size() > 0))
  {
    cout << "TIME      " << Utils::Format(time, 5)
                         << Utils::Format((UINT)this->freeMachines.size(), 5) << endl;
    bool changeMade = false;
    // the boolean and this inner loop are here in case there is
    // more than one voter done at the same time
    bool thingsToDoThisTick = true;
	//By using a boolean to verify if there is another process to be done on this loop
	//iteration and a series of if statements, we can make sure that no process is
	//overlooked and that the loop doesn't run too much.
    while(thingsToDoThisTick)
    {
      thingsToDoThisTick = false;

      // we see if a voter is done voting at this time
      // if so
      //     we mark the voter as done
      //     erase from the 'votersVoting' 'multimap'
      //     and insert into the 'doneVoting' 'multimap'
      multimap<int, OneVoter>::iterator iter = this->votersVoting.begin();
      if (time == (iter->second).getTimeDoneVoting())
      {
        // we have a voter done at this time
        // mark the voter as done
        // erase from the 'voting' multimap
        // then assign the next voter to that machine
		//The below boolean change will keep the loop running, not killing
		//the program when it shouldn't be killed.
        thingsToDoThisTick = true;
        changeMade = true;
        cout << "VOTER DONE  " << time << ": " << (iter->second).toString() << endl;
        OneVoter oneVoter = iter->second;
        int whichMachine = oneVoter.getMachineNumber();
        this->freeMachines.push_back(whichMachine);
        oneVoter.doneVoting();
        this->votersVoting.erase(iter);
        this->votersDoneVoting.insert(std::pair<int, OneVoter>(time, oneVoter));
      } // if (time == (iter->second).getTimeDoneVoting())
       
      // if there are voters pending and a free machine
      //     if the pending voter arrived lessequal "now"
      //         assign that voter to the zeroth free machine
      //         erase that machine from the list of free machines
      //         erase that voter from the 'votersPending' 'multimap'
      //         and insert the voter into the 'votersVoting' 'multimap'
      if ((this->freeMachines.size() > 0) && (this->votersPending.size() > 0))
      {
        OneVoter nextVoter = (this->votersPending.begin())->second;
        if (nextVoter.getTimeArrival() <= time)
        {
		  //This also does the same as the above boolean change, allowing the
		  // program to advance when it needs to and not die.
          thingsToDoThisTick = true;
          changeMade = true;
          int whichMachine = this->freeMachines[0];
          this->freeMachines.erase(this->freeMachines.begin());
          nextVoter.assignMachine(whichMachine, time); 
          cout << "ASSIGNED    " << time << ": " << nextVoter.toString() << "\n";
          this->votersPending.erase(this->votersPending.begin());
          int leaveTime = nextVoter.getTimeDoneVoting();
          this->votersVoting.insert(std::pair<int, OneVoter>(leaveTime, nextVoter));
        }
      } // if ((this->freeMachines.size() > 0) && (this->votersPending.size() > 0))
    } // while(thingsToDoThisTick)

//    if (changeMade)
//    {
//      cout << "Current queues" << endl;
//      cout << this->toString() << endl;
//    }

    ++time;
  } // while ((this->votersPending.size() > 0) || (this->votersVoting.size() > 0))

  cout << "leave runSimulation2" << endl;
}

/******************************************************************************
 * Function 'toString'.
 * This is the usual 'toString' to output the basic data of this class.
 *
 * Returns:
 *   the 'toString'
**/
string Queue::toString()
{
  string s = "";
  multimap<int, OneVoter>::iterator iter;

  s += "PENDING VOTERS\n";
  //The only way anything in this function could break would be if it was out of
  //bounds, and we cannot get there from here because we are using 'this' and 
  //container iterators in order to make sure we do not run out of bounds.
  for (iter = this->votersPending.begin();
       iter != this->votersPending.end(); ++iter)
  {
    s += (iter->second).toString() + "\n";
  }

  s += "\nVOTING VOTERS\n";
  for (iter = this->votersVoting.begin();
       iter != this->votersVoting.end(); ++iter)
  {
    s += (iter->second).toString() + "\n";
  }

  s += "\nDONE VOTING VOTERS\n";
  for (iter = this->votersDoneVoting.begin();
       iter != this->votersDoneVoting.end(); ++iter)
  {
    s += (iter->second).toString() + "\n";
  }

  s += "\n********** ********** ********** ********** ********** **********\n";

  return s;
}
