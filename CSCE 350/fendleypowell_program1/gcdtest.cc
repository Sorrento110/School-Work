#include "gcdtest.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'GCDTest' for testing gcd algorithms.
 *
 * Author/copyright:  Powell Fendley. All rights reserved.
 * Date: 9 September 2016
**/

/******************************************************************************
 * Constructor
**/
GCDTest::GCDTest() {
}

/******************************************************************************
 * Destructor
**/
GCDTest::~GCDTest() {
}

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function to create the numbers to be tested.
**/
void GCDTest::CreateNumbers(LONG how_many_tests, LONG max_test_number_size)
{
  cout << "create " << how_many_tests << " records" << endl;

  MyRandom myrandom;
  LONG upperlimit = max_test_number_size;

  for (int i = 0; i < how_many_tests; ++i) {
    LONG a = myrandom.RandomUniformInt(0, upperlimit);
    LONG b = myrandom.RandomUniformInt(0, upperlimit);
    veca_.push_back(a);
    vecb_.push_back(b);
  }

  cout << "done with creation of " << how_many_tests << " records" << endl;
}

/******************************************************************************
 * Function to format a progress line.
**/
string GCDTest::FormatProgress(LONG sub, LONG a, LONG b,
                               LONG g, LONG g3)
{
  string s = "";
  s += Utils::Format(sub, 11) + " ";
  s += Utils::Format(a, 11) + " ";
  s += Utils::Format(b, 11) + " ";
  s += Utils::Format(g, 8) + " ";
  s += Utils::Format(g3, 8);

  if ((g > 0) && (g3 > 0) && (g != g3)) {
    s += " GCDS NOT EQUAL";
  }
  return s;
}

/*********************************************************************
 * Naive gcd using algorithm on .pdf for assignment.
**/
LONG GCDTest::GcdNaive(LONG a, LONG b)
{
  LONG larger;
  LONG smaller;
  if(a > b)
  {
    larger = a;
    smaller = b;
  }
  else
  {
    larger = b;
    smaller = a;
  }
  LONG remains = 1;
  //cout << a << " " << b;
  while(remains != 0)
  {
    remains = larger % smaller;
    //cout << "Modded";
    count_divisions_naive_++;
    //cout << "Divi Up";
    larger = smaller;
    smaller = remains;
  }
  qt1_ = larger;
  return remains;
}

/*********************************************************************
 * Subtract three times gcd
**/
LONG GCDTest::GcdSubtract(LONG a, LONG b)
{
  LONG larger;
  LONG smaller;
  LONG largerHolder;
  LONG remains = 1;
  if(a > b)
  {
    larger = a;
    smaller = b;
  }
  else
  {
    larger = b;
    smaller = a;
  }
  largerHolder = larger;
  //cout << "starts program" << endl;
  while(remains != 0)
  {
    largerHolder = largerHolder - smaller*2;
    count_subtractions_ ++;
    //subtraction count for comparison below
    count_subtractions_++;
    if(largerHolder < 0)
    {
      remains = larger - smaller;
      larger = smaller;
      largerHolder = smaller;
      smaller = remains;
      continue;
    }
    largerHolder -= smaller;
    count_subtractions_ ++;
    //subtraction count for comparison below
    count_subtractions_++;
    if(largerHolder < 0)
    {
      remains = larger - smaller*2;
      larger = smaller;
      largerHolder = smaller;
      smaller = remains;
      continue;
    }
    largerHolder -= smaller;
    count_subtractions_ ++;
    //subtraction count for comparison below
    count_subtractions_++;
    if(largerHolder < 0)
    {
      remains = larger - smaller*3;
      larger = smaller;
      largerHolder = smaller;
      smaller = remains;
      continue;
    }
    else
    {
      remains = larger % smaller;
      count_divisions_subtract_++;
      larger = smaller;
      largerHolder = smaller;
      smaller = remains;
    }
  }
  qt2_=largerHolder;
  return remains;


}

/*********************************************************************
**/
void GCDTest::RunTheTests()
{
  double timenew;
  string timestring;

  // test naive
  timestring = Utils::TimeCall("bef naive false", timenew);
  cout << timestring << endl;
  TestNaive(false);
  timestring = Utils::TimeCall("aft naive false", timenew);
  cout << timestring << endl;

  // test subtract
  timestring = Utils::TimeCall("bef subtract false", timenew);
  cout << timestring << endl;
  TestSubtract(false);
  timestring = Utils::TimeCall("aft subtract false", timenew);
  cout << timestring << endl;

  // test naive with the secondary test
  timestring = Utils::TimeCall("bef naive true", timenew);
  cout << timestring << endl;
  TestNaive(true);
  timestring = Utils::TimeCall("aft naive true", timenew);
  cout << timestring << endl;

  // test subtract with the secondary test
  timestring = Utils::TimeCall("bef subtract true", timenew);
  cout << timestring << endl;
  TestSubtract(true);
  timestring = Utils::TimeCall("aft subtract true", timenew);
  cout << timestring << endl;

  // test naive against subtract
  timestring = Utils::TimeCall("bef n-sub false", timenew);
  cout << timestring << endl;
  TestNaiveSubtract();
  timestring = Utils::TimeCall("aft n-sub false", timenew);
  cout << timestring << endl;

  cout << "done with the computation" << endl;
}

/*********************************************************************
**/
void GCDTest::TestNaive(bool check_result) {

  LONG f, f2, r;
  count_divisions_naive_ = 0;
  int i = 0;

  for(UINT i = 0; i < veca_.size(); i++)
  {
    //cout << "Starting Trial ";
    f = veca_.at(i);
    //cout << "Stored f* ";
    f2 = vecb_.at(i);
    //cout << "Stored f2* ";
    this->GcdNaive(f, f2);
    cout << "Test Number: " << i << " First Number: " << f << " Second Number: "
     << f2 << " GCD: " << qt1_ << endl;
    //cout << "Hello";
  }

  cout << "Number of naive divisions " << count_divisions_naive_ << endl;

}

/*********************************************************************
**/
void GCDTest::TestNaiveSubtract() {
  LONG a, b, g, g3;

  count_divisions_naive_ = 0;
  count_subtractions_ = 0;
  count_divisions_subtract_ = 0;
  for (UINT i = 0; i < veca_.size(); ++i) {
    a = veca_.at(i);
    b = vecb_.at(i);
    g = this->GcdNaive(a, b);
    g3 = this->GcdSubtract(a, b);

    if (g != g3) {
      cout << "ERROR N-SUB" << a << " " << b << " " << g << " " << g3 << endl;
    }
  }
  cout << "Test naive against subtract shows no discrepancies" << endl;
}

/*********************************************************************
**/
void GCDTest::TestSubtract(bool check_result) {

  LONG f, f2, r;
  count_subtractions_ = 0;
  count_divisions_subtract_ = 0;
  //cout << "Hello";
  for(UINT i = 0; i < veca_.size(); i++)
  {
    f = veca_.at(i);
    //cout << "Gets to the fist";
    f2 = vecb_.at(i);
    //cout << "Gets to the second";
    this->GcdSubtract(f, f2);
    cout << "Test Number: " << i << " First Number: " << f <<
    " Second Number: " << f2 << " GCD: " << qt2_ << endl;
  }

  cout << "Number of subtractions and divisions " << count_subtractions_
       << " " << count_divisions_subtract_ << endl;
}
