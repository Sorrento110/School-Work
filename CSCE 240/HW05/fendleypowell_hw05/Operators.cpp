#include "SetOfWords.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Operators' for the indexing program.
 *
 * Author: Powell Fendley
 * Date last modified: 26 March 2015
**/

static string TAG = "Operators: ";

/******************************************************************************
 * Overloaded operator '<<' for 'SetOfWords' instances.
 * This invokes the 'toString'.
 *
 * Returns:
 *   the 'toString'
**/
ostream& operator <<(ostream& outputStream, const SetOfWords& theSet)
{
  theSet.toString();
}

/******************************************************************************
 * Overloaded operator '<<' for 'Index' instances.
 * This invokes the 'toString'.
 *
 * Returns:
 *   the 'toString'
**/
ostream& operator <<(ostream& outputStream, const Index& theIndex)
{
  theIndex.toString();
}
