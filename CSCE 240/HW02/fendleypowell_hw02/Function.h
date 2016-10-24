/****************************************************************
 * Header file for the function class for the numerical
 * integration program.
 *
 * This class is simply a wrapper for the static function f(x).
 *
 * Author/copyright:  Duncan Buell
 * Used by: Powell Fendley
 * Date: 12 January 2015
 *
**/

#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
using namespace std;

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

class Function
{
public:
  Function();
  virtual ~Function();

  static double f(double x);

private:
};

#endif
