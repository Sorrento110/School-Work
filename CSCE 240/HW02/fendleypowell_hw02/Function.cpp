#include "Function.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Function' for the numerical integration computation.
 *
 * In this case, the class is merely a wrapper for the function
 *   f(x) = x^2 + 1.0
 *
 * All arithmetic is done in double precision.
 *
 * Author: Duncan A. Buell
 * Used by: Powell Fendley
 * Date last modified: 12 January 2015
**/

/******************************************************************************
 * Constructor
**/
Function::Function()
{
}

/******************************************************************************
 * Destructor
**/
Function::~Function()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'f'.
 * This function computes the value of 'f' at the point 'x'.
 * This particular function is
 *   f(x) = x^2 + 1.0
 *
 * Parameters:
 *   x - the 'double' point at which to evaluate the function
 *
 * Returns:
 *   the value of 'f' at 'x'
**/
double Function::f(double x)
{
  return x*x + 1.0;
}
