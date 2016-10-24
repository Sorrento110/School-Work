#include "TrapezoidMethod.h"
#include <iostream>
#include <sstream>
/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 *
 * Author: Powell Fendley
 * Date last modified: February 3 2015
**/

/******************************************************************************
 * Constructor
**/
TrapezoidMethod::TrapezoidMethod()
{
int numberOfTraps=0;
double leftPoint=0;
double rightPoint=0;
double interval;
}

/******************************************************************************
 * Destructor
**/
TrapezoidMethod::~TrapezoidMethod()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions
**/

/******************************************************************************
 * Function 'computeArea'.
**/
double TrapezoidMethod::computeArea()
{
Function fun;
double area=0;
readData();
double holder=leftPoint;//Making holders for the start point and end point.
double holder2=leftPoint+interval;
while(holder2<=rightPoint)
{
area=area+((holder2-holder)*(fun.f(holder)+fun.f(holder2)))/2.0;
holder=holder+interval;
holder2=holder2+interval;
}
return area;
}

/******************************************************************************
 * Function 'readData'.
**/
void TrapezoidMethod::readData()
{
cin >> leftPoint;
cin >> rightPoint;
cin >> numberOfTraps;
interval=(rightPoint-leftPoint)/numberOfTraps;
}

/******************************************************************************
 * Function 'toString'.
**/
string TrapezoidMethod::toString()
{
string leftP;
string rightP;
string numb;
ostringstream convert;
convert << leftPoint;
leftP=convert.str();
convert.str("");
convert << rightPoint;
rightP=convert.str();
convert.str("");
convert << numberOfTraps;
numb=convert.str();
string ret="Left Point:"+leftP+" Right Point:"+rightP+" Number of Trapezoids:"+numb;
return ret;
}
