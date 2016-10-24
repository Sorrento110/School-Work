/****************************************************************
 * Header file for a node in a tree.
 *
 * Author/copyright:  Duncan Buell
 * Date: 1 January 2015
 *
**/

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

class Node
{
public:
  Node();
  Node(int sequence);
  Node(string initString);
  virtual ~Node();

  int getPayoff() const;
  int getSequence() const;
  vector<int> getDownLinks();
  bool getVisited() const;
  void setVisited(bool newval);

  string toString() const;

private:
  bool visited;
  int payoff;
  int sequence;
  int num;

  vector<int> downLinks;
  string buff;
  stringstream splitt();
  vector<string> splitter;
};

#endif
