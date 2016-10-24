/****************************************************************
 * Header file for the application class for the indexing program.
 *
 * Author/copyright:  Powell Fendley
 * Date: 26 March 2015
 *
**/

#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <map>
#include <set>
using namespace std;

#include "../../Utilities/Utils.h"
#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

#include "Dictionary.h"
#include "Stoplist.h"

class Index
{
public:
  Index();
  virtual ~Index();

  void initialize();
  void createIndex(Scanner& inStream, Dictionary& dictionary,
                                      const Stoplist& stoplist);
  string toString();
  string toStringLocalStoplist();

  friend const ostream& operator <<(ostream& outputStream, const Index& theIndex);

private:
  set<string> localStoplist;

  map<int, string > theIndex;

  void parseLine(int lineCounter, ScanLine& scanLine, Dictionary& dictionary,
                                                      Stoplist stoplist);
  bool tokenIsNumeric(string token);
  bool tokenIsPlural(string token);

  int linecounter;
  string line;
  string holder;
  string token;
  ScanLine linner;
  string::const_iterator iter;
  
};

#endif
