#include "Main.h"

/****************************************************************
 * Main program for Homework 4.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Date: 1 January 2015
 *
**/

static const string TAG = "Main: ";

int main(int argc, char *argv[])
{
  int payoff = 0;
  string inFileName = "";
  string outFileName = "";
  string logFileName = "";
  ofstream outStream;

  Scanner inStream;

  Traversal traversal;

  Utils::CheckArgs(3, argc, argv, "infilename outfilename logfilename");
  inFileName = static_cast<string>(argv[1]);
  outFileName = static_cast<string>(argv[2]);
  logFileName = static_cast<string>(argv[3]);

  Utils::LogFileOpen(logFileName);
  Utils::FileOpen(outStream, outFileName);

  Utils::logStream << TAG << "Beginning execution\n";
  Utils::logStream.flush();

  Utils::logStream << TAG << "infile '" << inFileName << "'\n";
  Utils::logStream << TAG << "outfile '" << outFileName << "'\n";
  Utils::logStream << TAG << "logfile '" << logFileName << "'\n";

  inStream.openFile(inFileName);

  traversal.initialize(inStream);
  outStream << TAG << "Tree is\n" << traversal.toString() << endl;
  
  payoff = traversal.traverse();
  outStream << TAG << "Payoff is " << Utils::Format(payoff, 5) << endl;

  Utils::logStream << TAG << "Ending execution\n";
  Utils::logStream.flush();

  Utils::FileClose(outStream);
  Utils::FileClose(Utils::logStream);

  return 0;
}
