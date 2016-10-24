#include "Main.h"

/*******************************************************************************
 * 45678901234567890123456789012345678901234567890123456789012345678901234567890
 * Main program for Homework 2.
 *
 * This program approximates the area under the curve of a positive function
 * using the trapezoid method.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Used by: Powell Fendley
 * Date: 12 January 2015
**/

int main(int argc, char *argv[])
{
  double areaUnderCurve = 0.0;

  TrapezoidMethod trapezoid;

  trapezoid.readData(); // reads from stdin 
  areaUnderCurve = trapezoid.computeArea();
  cout << "Conditions are:\n" << trapezoid.toString() << endl; 
  cout << "Approximate area under curve is  "
       << Utils::Format(areaUnderCurve, 10, 6) << endl;

  return 0;
}

