#include "Queue.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Queue' for the queueing theory computation.
 *
 * Author: Powell Fendley
 * Date last modified: 9 April 2015
**/
//Initializing Variables
 int howManyVoters;
 int howManyMachinesLower;
 int howManyMachinesUpper;

 vector<int> freeMachines;

 multimap<int, OneVoter> votersBackup;
 multimap<int, OneVoter> votersPending;
 multimap<int, OneVoter> votersVoting;
 multimap<int, OneVoter> votersDoneVoting;


/******************************************************************************
 * Constructor
**/
Queue::Queue()
{
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
**/
void Queue::computeMeanAndDev(double& mean, double& dev)
{
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
  for (iterMultimap = this->votersDoneVoting.begin();
       iterMultimap != this->votersDoneVoting.end(); ++iterMultimap)
  {
    OneVoter voter = iterMultimap->second;
    int waitTime = voter.getTimeWaiting();
    waitTimeMap[waitTime] = waitTimeMap[waitTime] + 1;
  }

  int timeLower = (waitTimeMap.begin())->first;
  int timeUpper = (waitTimeMap.rbegin())->first;
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
 * This is the function that runs the actual simulation.
**/
void Queue::runSimulation()
{
  //Program doesn't make it to even the cout, though it's called in main.
  //I don't know if this is a prolem with my computer but I cannot seem to fix
  //it.
  cout << "Made it to loop start";
  for(int i=howManyMachinesLower; i<=howManyMachinesUpper; i++)
  {
    cout << "stored first voter list into pending";
    votersPending=votersBackup;
    cout << "made it to run sim";
    runSimulation2(i);
  }
  doStatistics();
}

/******************************************************************************
 * Function 'runSimulation2'.
**/
void Queue::runSimulation2(int howManyMachines)
{
  int time=0;//Keeps track of the time we are looking at for arrival.
  int innertime=0; //Keeps track of the real time taken to vote.
  freeMachines.resize(howManyMachines);
  for(int i=0; i<freeMachines.size(); i++)
  {
    int machine=i;
    freeMachines[i]=machine;
  }
  cout << "made it to assigning machines to vector";
  pair <multimap<int,OneVoter>::iterator, multimap<int,OneVoter>::iterator> it;
  while(!votersPending.empty())
  {
    //Calling the voters in pending at the specified time.
    votersVoting.insert(pair<int, OneVoter>(1, votersPending.find(time)->second));
    it = votersVoting.equal_range(1);
    while(!votersVoting.empty())
    {
      //Using an iterator to access elements in multimap if there are
      //multiple arriving at the same time.
      for (multimap<int,OneVoter>::iterator iter=it.first; iter!=it.second; ++iter)
      {
        if(!freeMachines.empty())
        {
          if(iter->second.getTimeDoneVoting()==0)
          {
            iter->second.assignMachine(freeMachines.back(), innertime);
            freeMachines.pop_back();
            iter->second.doneVoting();
            cout << iter->second.getMachineNumber() << " " << iter->second.getTimeDoneVoting();
          }
        }
        else if(innertime==iter->second.getTimeDoneVoting())
        {
          freeMachines.push_back(iter->second.getMachineNumber());
          votersVoting.erase(iter);
        }
        innertime++;
      }
    }
    votersVoting.clear();
    time++;
  }
}

/******************************************************************************
 * Function 'toString'.
 * This is the usual 'toString' to output the basic data of this class.
**/
string Queue::toString()
{
  string s = "";
  return s;
}
