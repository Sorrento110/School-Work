#include "main.h"

/****************************************************************
 * Main program for Homework 1.
 *
 * Author/copyright:  Powell Fendley. All rights reserved.
 * Date: 9 September 2016
 *
**/

static const string kTag = "MAIN: ";

/*********************************************************************
**/
int main(int argc, char *argv[]) {
  LONG how_many_tests;
  LONG max_test_number_size;
  double timenew = 0.0;
  string data_filename = "";
  string timestring = "";

  Scanner in_scanner;

  GCDTest gcdtest;

  Utils::CheckArgs(1, argc, argv, "datafilefilename");
  data_filename = static_cast<string>(argv[1]);

  cout << kTag << "Beginning execution\n";

  cout << kTag << "datafile  '" << data_filename << "'\n";

  timestring = Utils::TimeCall("beginning", timenew);
  cout << timestring << endl;

  in_scanner.OpenFile(data_filename);
  if (in_scanner.HasNext()) {
    how_many_tests = in_scanner.NextLONG();
    max_test_number_size = in_scanner.NextLONG();
  } else {
    cout << "ERROR: no data in input file" << endl;
    exit(0);
  }

  cout << "start the computation" << endl;

  gcdtest = GCDTest();
  gcdtest.CreateNumbers(how_many_tests, max_test_number_size);

  timestring = Utils::TimeCall("done creation", timenew);
  cout << timestring << endl;

  timestring = Utils::TimeCall("before gcdtest", timenew);
  cout << timestring << endl;

  gcdtest.RunTheTests();

  timestring = Utils::TimeCall("after gcdtest", timenew);
  cout << timestring << endl;

  cout << kTag << "Ending execution\n";

  timestring = Utils::TimeCall("ending", timenew);
  cout << timestring << endl;

  return 0;
}
