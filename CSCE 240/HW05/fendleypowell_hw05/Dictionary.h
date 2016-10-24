/****************************************************************
 * Header file for the dictionary class for the indexing program.
 *
 * Author/copyright:  Duncan Buell
 * Date: 11 January 2015
 *
**/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <set>
using namespace std;

#include "../../Utilities/Utils.h"
#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

#include "SetOfWords.h"

class Dictionary : public SetOfWords
{
public:
  Dictionary();
  virtual ~Dictionary();

  string addWord(string word);

private:
};

#endif
