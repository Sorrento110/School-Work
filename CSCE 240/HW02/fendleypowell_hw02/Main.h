/****************************************************************
 * Rather generic header file that includes the 'Utilities' code.
 *
 * Author/copyright:  Duncan Buell
 * Used by: Powell Fendley
 * Date: 28 December 2014
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

#include "TrapezoidMethod.h"

class Main
{
public:
  int main();
  virtual ~Main();

private:

};

#endif // MAIN_H
