/****************************************************************
 * Header file for the class to traverse a tree recursively.
 *
 * Author/copyright:  Duncan Buell
 * Date: 1 January 2015
 *
**/

#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "Node.h"

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

class Traversal
{
public:
  Traversal();
  virtual ~Traversal();

  void initialize(Scanner& inStream);
  string toString() const;
  int traverse();

private:
  int totalPayoff;
  int i;//loop iterator

  Node headNode;
  Node workwith;

  map<int, Node> theNodes;
  vector<int> workwithvecs;
  string returner;

  int traverseInner(const int& level);
};

#endif
