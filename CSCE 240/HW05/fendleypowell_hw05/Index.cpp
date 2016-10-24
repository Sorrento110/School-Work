#include "Index.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Index' for the indexing program.
 *
 * Author: Powell Fendley
 * Date last modified: 26 March 2015
**/

static string TAG = "Index: ";

/******************************************************************************
 * Constructor
**/
Index::Index()
{
  map<int, string > theIndex;
  set<string> localStoplist;
  int linecounter=0;
}

/******************************************************************************
 * Destructor
**/
Index::~Index()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'createIndex'.
**/
void Index::createIndex(Scanner& inStream, Dictionary& dictionary,
                                           const Stoplist& stoplist)
{
  ScanLine linner;
  while(inStream.hasNext())
  {
    string line=inStream.nextLine();
    linner.openString(line);
    parseLine(linecounter, linner, dictionary, stoplist);
    linecounter++;
  }
}

/******************************************************************************
 * Function 'parseLine'.
**/
void Index::parseLine(int lineCounter, ScanLine& scanLine,
                      Dictionary& dictionary, Stoplist stoplist)
{ 
  string holder;
  while(scanLine.hasNext())
  {
    string token=scanLine.next();
  //Make decision on token
    if(token=="<<")//it is assumed closing '>>' token is on the same line.
    {
      break;
    }
    if(!tokenIsNumeric(token)&&!stoplist.containsWord(token))
    {
      if(!dictionary.containsWord(token))
      {
        dictionary.addWord(token);
      }
      holder+=token+" ";
    }
  }
  theIndex[lineCounter]=holder;
//Use Linecounter everytime to get line number.
}

/******************************************************************************
 * Function 'tokenIsNumeric'.
**/
bool Index::tokenIsNumeric(string token)
{
 //check if token passed is numeric
  string::const_iterator iter = token.begin();
  while (iter != token.end() && std::isdigit(*iter))
  {
    iter++;
  }
  return !token.empty() && iter == token.end();
//Efficient method above was found at: http://stackoverflow.com and modified.
}

/******************************************************************************
 * Function 'tokenIsPlural'
**/
bool Index::tokenIsPlural(string token)
{
//check if token passed is plural.
}

/******************************************************************************
 * Function 'toString'.
**/
string Index::toString()
{
//print out the entire theIndex map.
  typedef map<int, string>::const_iterator mapIter;
  for(mapIter iter = theIndex.begin(); iter != theIndex.end(); iter++)
  {
    cout << "Line: " << iter->first << " Content: " << iter->second << endl;
  }
}
