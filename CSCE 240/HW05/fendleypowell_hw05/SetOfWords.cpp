#include "SetOfWords.h"
#include <iostream>
#include <fstream>

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'SetOfWords' for the indexing program.
 *
 * Author: Powell Fendley
 * Date last modified: 26 March 2015
**/

static string TAG = "SetOfWords: ";

set<string> theWords;
set<string>::iterator it;

/******************************************************************************
 * Constructor
**/
SetOfWords::SetOfWords()
{
}

/******************************************************************************
 * Destructor
**/
SetOfWords::~SetOfWords()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'containsWord'.
**/
bool SetOfWords::containsWord(string word)
{
//Check the set to see if object is contained.
//Use set's find and check if the iterator stored is equal to the set's end.
  it=theWords.find(word);
  if(it != theWords.end())
  {
    return true;
  }
}

/******************************************************************************
 * Function 'addWord'
**/
bool SetOfWords:: addWord(const string& word)
{
  theWords.insert(word);
  return true;
}

/******************************************************************************
 * Function 'initialize'.
**/
void SetOfWords::initialize(const string& fileName)
{
//take in file and read all lines and add to theWords
  Scanner dataStream;
  dataStream.openFile(fileName);
  string holder;
  while(dataStream.hasNext())
  {
    holder=dataStream.nextLine();
    addWord(holder);
  }

}

/******************************************************************************
 * Function 'toString'.
**/
string SetOfWords::toString()
{
//Print all words in theWords.
  string holder;
  for(it=theWords.begin(); it!=theWords.end(); it++)
  {
    holder+=(*it)+'\n';
  }
  return holder;
}
