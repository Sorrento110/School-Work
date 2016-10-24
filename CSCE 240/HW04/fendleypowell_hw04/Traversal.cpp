#include "Traversal.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Traversal' for playing part of a dominos game.
 *
 * Author: Powell A. Fendley
 * Date last modified: 5 March 2014
**/

static const string TAG = "Traversal: ";

map<int, Node> theNodes;
int totalPayoff;
int runningsum=0;
Node headNode;

/******************************************************************************
 * Constructor
**/
Traversal::Traversal()
{
}

/******************************************************************************
 * Destructor
**/
Traversal::~Traversal()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'initialize'.
**/
void Traversal::initialize(Scanner& inStream)
{
#ifdef EBUG
 Utils::logStream << TAG << "enter initialize\n"; 
#endif

  // first we read the data
  while (inStream.hasNext())
  {
    string nextLine = inStream.nextLine();
    Node newNode = Node(nextLine);
    this->theNodes[newNode.getSequence()] = newNode;
  }

  // now we fill in the leaf nodes
  // first we have to find the min and the max node sequence numbers
  int minSeq = (this->theNodes.begin())->first;
  int maxSeq = (this->theNodes.rbegin())->first;
  for (map<int, Node>::iterator iter = this->theNodes.begin();
                                iter != this->theNodes.end(); ++iter)
  {
    vector<int> theLinks = (iter->second).getDownLinks();
    for (vector<int>::iterator iter2 = theLinks.begin();
                               iter2 != theLinks.end(); ++iter2)
    {
      if ((*iter2) > maxSeq)
      {
        maxSeq = (*iter2);
      }
    }
  }

//  cout << "min and max " << minSeq << " " << maxSeq << endl;

  // now we add the leaf nodes to the 'map'
  // note we loop inclusive of the upper endpoint
  for (int seq = minSeq; seq <= maxSeq; ++seq)
  {
    if (0 == this->theNodes.count(seq))
    {
      Node newNode = Node(seq);
      this->theNodes[seq] = newNode;
    }
  }

//  cout << this->toString();

#ifdef EBUG
 Utils::logStream << TAG << "leave initialize\n"; 
#endif
}

/******************************************************************************
 * Function 'traverse'.
**/
int Traversal::traverse()
{
#ifdef EBUG
 // Utils::logStream << TAG << "enter traverse\n"; 
#endif

totalPayoff=traverseInner((this->theNodes.begin())->first);

#ifdef EBUG
 // Utils::logStream << TAG << "leave traverse\n"; 
#endif
  return this->totalPayoff;
}

/******************************************************************************
 * Function 'traverse'.
**/
int Traversal::traverseInner(const int& level)
{
#ifdef EBUG
 // Utils::logStream << lead << TAG << "enter traverseInner" << node.toString() << endl; 
#endif

Node workwith=theNodes.at(level);
vector<int> workwithvec=workwith.getDownLinks();
if(workwithvec.empty())
{
  int num=workwith.getPayoff();
  runningsum+=num;
}
else
{
  for(int i=0; i<workwithvec.size(); i++)
  {
    if(find(workwithvec.begin(), workwithvec.end(), i)!=workwithvec.end()+1)
    {
      this->traverseInner(workwithvec.at(i));
    }
  }  
}
return runningsum;

#ifdef EBUG
 // Utils::logStream << lead << TAG << "leave traverseInner\n"; 
#endif
}

/******************************************************************************
 * Function 'toString'.
 * This function dumps the 'map' of all nodes to a 'string' and returns it.
 *
 * Returns:
 *   the 'toString' of the data in the class
**/
string Traversal::toString() const
{
#ifdef EBUG
 //Utils::logStream << TAG << "enter toString\n"; 
#endif

for(int i=0; i<theNodes.size(); i++)
{
  string returner="";
  Node workwith=theNodes.at(i);
  //level prints to file
  vector<int> workwithvec=workwith.getDownLinks();
  for(int i=0; i<workwithvec.size(); i++)
  {
    //Downlink prints to file 
  }
}
return returner;

#ifdef EBUG
 // Utils::logStream << TAG << "leave toString\n"; 
#endif
}
