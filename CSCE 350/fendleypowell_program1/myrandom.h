/****************************************************************
 * Header file for the random number generator.
 *
 * Author/copyright:  Powell Fendley. All rights reserved.
 * Date: 9 September 2016
 *
**/

#ifndef MYRANDOM_H
#define MYRANDOM_H

#include <iostream>
#include <random>
#include <cassert>
using namespace std;

#include "../../Utilities/scanner.h"
#include "../../Utilities/scanline.h"

#undef NDEBUG

class MyRandom {
public:
 MyRandom();
 MyRandom(unsigned seed);
 virtual ~MyRandom();

 int RandomExponential(double lambda);
 double RandomNormal(double mean, double dev);
 double RandomUniformDouble(double lower, double upper);
 int RandomUniformInt(int lower, int upper);

private:
 unsigned int seed_;

 std::mt19937 generator_;
};

#endif
