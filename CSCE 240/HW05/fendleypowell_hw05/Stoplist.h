/****************************************************************
 * Header file for the stoplist class for the indexing program.
 *
 * Author/copyright:  Duncan Buell
 * Date: 11 January 2015
 *
**/

#ifndef STOPLIST_H
#define STOPLIST_H

#include <iostream>
#include <set>
using namespace std;

#include "../../Utilities/Utils.h"
#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

#include "SetOfWords.h"

class Stoplist : public SetOfWords
{
public:
  Stoplist();
  virtual ~Stoplist();

private:
};

#endif
