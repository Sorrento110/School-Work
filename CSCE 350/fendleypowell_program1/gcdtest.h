/****************************************************************
 * Header file for the gcd test.
 *
 * Author/copyright:  Powell Fendley. All rights reserved.
 * Date: 9 September 2016
 *
**/

#ifndef GCDTEST_H
#define GCDTEST_H

#include <iostream>
#include <vector>
using namespace std;

#include "../../Utilities/scanner.h"
#include "../../Utilities/scanline.h"

#include "myrandom.h"

class GCDTest {
public:
 GCDTest();
 virtual ~GCDTest();

 void CreateNumbers(LONG how_many_tests, LONG max_test_number_size);
 void RunTheTests();
 string stringifyBitLengthFreqs();
 string stringifyShiftFracFreqs();

private:
 LONG count_divisions_naive_ = 0;
 LONG count_divisions_subtract_ = 0;
 LONG count_subtractions_ = 0;
 LONG qt1_, qt2_, qt3_, qtx_;

// string ConvertToBinary(LONG n);
 string FormatProgress(LONG sub, LONG a, LONG b,
                       LONG g, LONG g3);
//                       LONG g, LONG gbin, LONG g3);
 LONG GcdNaive(LONG a, LONG b);
 LONG GcdSubtract(LONG a, LONG b);

 vector<LONG> veca_;
 vector<LONG> vecb_;

// void TestBinary(bool check_result);
// void TestBinarySubtract();
 void TestNaive(bool check_result);
// void TestNaiveBinary();
 void TestNaiveSubtract();
 void TestSubtract(bool check_result);

};

#endif
