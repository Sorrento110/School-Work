/****************************************************************
 * Header file for the 'SetOfWords' class.
 *
 * Author/copyright:  Duncan Buell
 * Used/Modified by: Powell Fendley
 * Date: 26 March 2015
 *
**/

#ifndef SETOFWORDS_H
#define SETOFWORDS_H

#include <iostream>
#include <set>
using namespace std;

#include "../../Utilities/Utils.h"
#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

class SetOfWords
{
public:
  SetOfWords();
  virtual ~SetOfWords();

  void initialize(const string& fileName);
  bool addWord(const string& word);
  bool containsWord(string word);
  string toString();

  friend const ostream& operator <<(ostream& outputStream, const SetOfWords& theSet);

private:
  ifstream myfile();
  string holder;
protected:
  set<string> theWords;
  set<string>::iterator it;

};

#endif
