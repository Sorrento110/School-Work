#include "Main.h"

/****************************************************************
 * Main program for Homework 5.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Used by: Powell Fendley
 * Date: 26 March 2015
 *
**/

static const string TAG = "Main: ";

int main(int argc, char *argv[])
{
  string stoplistFileName = "";
  string dataFileName = "";
  string dictionaryFileName = "";
  string outFileName = "";
  string logFileName = "";
  ofstream outStream;

  Scanner inStream;

  Dictionary dictionary;
  Index index;
  Stoplist stoplist;

  Utils::CheckArgs(5, argc, argv,
      "stoplistfilename dictionaryFileName datafilename outfilename logfilename");
  stoplistFileName = static_cast<string>(argv[1]);
  dictionaryFileName = static_cast<string>(argv[2]);
  dataFileName = static_cast<string>(argv[3]);
  outFileName = static_cast<string>(argv[4]);
  logFileName = static_cast<string>(argv[5]);

  Utils::LogFileOpen(logFileName);
  Utils::FileOpen(outStream, outFileName);

  Utils::logStream << TAG << "Beginning execution\n";
  Utils::logStream.flush();

  Utils::logStream << TAG << "stoplistfile '" << stoplistFileName << "'\n";
  Utils::logStream << TAG << "dictionaryfile '" << dictionaryFileName << "'\n";
  Utils::logStream << TAG << "datafile '" << dataFileName << "'\n";
  Utils::logStream << TAG << "outfile '" << outFileName << "'\n";
  Utils::logStream << TAG << "logfile '" << logFileName << "'\n";

  dictionary.initialize(dictionaryFileName);
  Utils::logStream << TAG << "Dictionary has been read\n" << endl;
  Utils::logStream << TAG << "Standard dictionary is\n"
                          << dictionary.toString() << endl;

  stoplist.initialize(stoplistFileName);
  Utils::logStream << TAG << "Stoplist has been read\n" << endl;
  Utils::logStream << TAG << "Standard stoplist is\n"
                   << stoplist.toString() << endl;
  
  inStream.openFile(dataFileName);
  index.createIndex(inStream, dictionary, stoplist);
  inStream.close();
  outStream << TAG << "Index is complete" << endl << endl;
  outStream << TAG << "Index is\n" << index.toString() << endl;

  Utils::logStream << TAG << "Ending execution\n";
  Utils::logStream.flush();

  Utils::FileClose(outStream);
  Utils::FileClose(Utils::logStream);

  return 0;
}
