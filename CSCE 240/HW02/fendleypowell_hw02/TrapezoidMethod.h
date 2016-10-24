/****************************************************************
 * Header file for the application class for the numerical
 * integration program.
 *
 * Author/copyright:  Duncan Buell
 * Used/Modified by: Powell Fendley
 * Date: 12 January 2015
 *
**/

#ifndef TRAPEZOIDRULE_H
#define TRAPEZOIDRULE_H

#include <iostream>
using namespace std;

#include "../../Utilities/Utils.h"

#include "Function.h"

class TrapezoidMethod
{
public:
  TrapezoidMethod();
  virtual ~TrapezoidMethod();

  double formula(int, int);
  double computeArea();
  void readData();
  string toString();

private:
  int numberOfTraps;
  double leftPoint;
  double rightPoint;
  double area;
  double interval;
  double holder;
  double holder2;
  Function fun;
  string ret;
  string leftP;
  string rightP;
  string numb;
};

#endif
