#include "Dictionary.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Dictionary' for the indexing program.
 *
 * Author: Powell Fendley
 * Date last modified: 26 March 2015
**/

static string TAG = "Dictionary: ";


/******************************************************************************
 * Constructor
**/
Dictionary::Dictionary() : SetOfWords()
{
}

/******************************************************************************
 * Destructor
**/
Dictionary::~Dictionary()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'addWord'.
 * This function redefines the function in the base class.
**/
string Dictionary::addWord(string word)
{
  theWords.insert(word);
  it=theWords.find(word+'s');
  if(it == theWords.end())
  { 
     theWords.insert(word+'s');
  }
  return word;
}
