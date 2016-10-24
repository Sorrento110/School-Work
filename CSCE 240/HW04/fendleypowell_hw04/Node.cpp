#include "Node.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Node' for a single node in a tree.
 *
 * Author: Powell Fendley
 * Date last modified: 5 March 2015
**/

static const string TAG = "Node: ";

int sequence, payoff;
bool visited=false;
vector<int> downLinks;
/******************************************************************************
 * Constructor
**/
Node::Node()
{
}

/******************************************************************************
 * Constructor -- we use this for the leaf nodes
**/
Node::Node(int sequence)
{
  sequence=sequence;
  payoff=sequence*sequence;
  cout << " Payoff Init From 1 construct:" << payoff;
}

/******************************************************************************
 * Constructor with an entire line of input data supplied
 * Data comes in as a parent num followed by a list of child node nums
**/
Node::Node(string initString)
{
  string buff;
  stringstream splitt(initString);//String Stream to split holder open by
  //whitespace and store them.
  vector<string> splitter;  //Vector to hold split stringstream parts
  while(splitt >> buff)
  {
    splitter.push_back(buff);
  }
  int num = atoi(splitter.at(0).c_str());
  sequence=num;
  payoff=sequence*sequence;
  for(int i=1; i<splitter.size(); i++)
  {
    int num = atoi(splitter.at(i).c_str());
    downLinks.push_back(num);
  }
}

/******************************************************************************
 * Destructor
**/
Node::~Node()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * Accessor 'getPayoff'.
 *
 * Returns:
 *   the payoff value of this node
**/
int Node::getPayoff() const
{
  return payoff;
}

/******************************************************************************
 * Accessor 'getSequence'.
 *
 * Returns:
 *   the sequence number of this node
**/
int Node::getSequence() const
{
  return sequence;
}

/******************************************************************************
 * Accessor 'getDownLinks'.
 *
 * Returns:
 *   the 'vector<int>' of the 'downLinks'
**/
vector<int> Node::getDownLinks()
{
  return downLinks;
}

/******************************************************************************
 * Accessor 'getVisited'.
 *
 * Returns:
 *   the 'bool' of 'visited'.
**/
bool Node::getVisited() const
{
  return visited;
}

/******************************************************************************
 * Mutator 'setVisited'.
 *
 * Sets:
 *    Sets the bool 'visited'
**/
void Node::setVisited(bool newval)
{
  visited=newval;
}

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'toString'.
 * This returns the data, formatted, from the class.
**/
string Node::toString() const
{
}
