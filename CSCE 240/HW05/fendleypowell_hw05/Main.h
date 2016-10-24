/****************************************************************
 * Rather generic header file that includes the 'Utilities' code.
 *
 * Author/copyright:  Duncan Buell
 * Used by: Powell Fendley
 * Date: 26 March 2015
 *
**/
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
using namespace std;

#include "../../Utilities/Utils.h"
#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

#include "Dictionary.h"
#include "Index.h"
#include "Stoplist.h"

class Main
{
public:
  int main();
  virtual ~Main();

private:

};

#endif // MAIN_H
