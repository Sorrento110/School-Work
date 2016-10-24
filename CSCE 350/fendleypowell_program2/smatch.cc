#include "smatch.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'SMatch' for testing gcd algorithms.
 *
 * Author/copyright:  Powell Fendley
 * Date: 10 October 2016
**/

/******************************************************************************
 * Constructor
**/
SMatch::SMatch() {
}

/******************************************************************************
 * Destructor
**/
SMatch::~SMatch() {
}

/******************************************************************************
 * General functions.
**/
/******************************************************************************
 * Function to create DNA strings.
void SMatch::CreateDNA() {
  string thedna = "";
  MyRandom myrandom;

  for (int i = 0; i < 100; ++i) {
    int r = myrandom.RandomUniformInt(0, 100);
    if (r < 50) {
      thedna += "A";
    } else if (r < 75) {
      thedna += "C";
    } else if (r < 90) {
      thedna += "T";
    } else {
      thedna += "G";
    }
  }
  cout << thedna << endl;
}
**/

/******************************************************************************
 * Function to find matches of patterns in the text.
**/
void SMatch::FindMatches() {
  string s = "";
  string textfull=ToStringText();

  for(vector<string>::iterator it = the_patterns_.begin();
                               it != the_patterns_.end(); ++it) {
    s = (*it);
    LoopThrough(s, textfull);
  }
}

/******************************************************************************
 * Child function of FindMatches to separate changing targets from comparing
 * characters in text and Targets.
**/
void SMatch::LoopThrough(string Target, string Text) {
  freq = 0;
  comparisons = 0;
  matches = 0;
  for(string::size_type i = 0; i < Text.length(); i++)
  {
    if(Text[i] == Target[0])
    {
      freq++;
      comparisons++;
      for(string::size_type j = 1; j < Target.length(); j++)
      {
        if(Target[j] == Text[i+j])
        {
          comparisons++;
          if(j == Target.length()-1)
          {
            matches++;
          }
        }
        else
        {
          break;
        }
      }
    }
    if(i + Target.length() >= Text.length())
    {
      break;
    }
  }
  compOfreq = (double) comparisons/(double) freq;
  cout << "Target: " << Target << " Comparisons: " << comparisons <<
  " Frequency: " << compOfreq << "\n";
  cout << "Matches: " << matches << "\n";
}

/******************************************************************************
 * Function to read the patterns.
**/
void SMatch::ReadPatterns(Scanner& in_scanner)
{
  while (in_scanner.HasNext()) {
    string input = in_scanner.NextLine();
    the_patterns_.push_back(input);
  }
}

/******************************************************************************
 * Function to read the text.
**/
void SMatch::ReadText(Scanner& in_scanner)
{
  while (in_scanner.HasNext()) {
    string input = in_scanner.NextLine();
    the_text_.push_back(input);
  }
}

/******************************************************************************
 * Function to 'ToString' the 'vector' of patterns.
**/
string SMatch::ToStringPatterns() {
  string s = "";

  for(vector<string>::iterator it = the_patterns_.begin();
                               it != the_patterns_.end(); ++it) {
    s += (*it) + "\n";
  }

  return s;
}


/******************************************************************************
 * Function to 'ToString' the 'vector' of text.
**/
string SMatch::ToStringText() {
  string s = "";

  for(vector<string>::iterator it = the_text_.begin();
                               it != the_text_.end(); ++it) {
    s += " " + (*it);
  }

  return s;
}
