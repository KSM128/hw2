#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    for(size_t i = 0; i < src.size(); i++){
      src[i] = std::tolower(static_cast<char>(src[i]));
    }
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  std::set<std::string> output;
  std::string trimmed = trim(rawWords);
  std::string tempKeyword;

  // go through trimmed string
  for(std::string::iterator it = trimmed.begin(); it != trimmed.end(); ++it){
    char c = *it;
    // if char isn't punc 
    if(!(std::ispunct(c) || std::isspace(c))){
      tempKeyword.push_back(c);
    } else {
      // upon punc, check for len >= 2
      if(tempKeyword.size() >= 2){
        // insert a lower case 
        output.insert(convToLower(tempKeyword));
      } 
      tempKeyword.clear();
    }

    // this is added to deal with puncs/space at end of word
    if(tempKeyword.size() >= 2){
      output.insert(convToLower(tempKeyword));
    }
  }

  return output;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
