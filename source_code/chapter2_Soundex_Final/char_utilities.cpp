/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#include "char_utilities.h"

namespace charutils {
char LowerCase(char c) { return static_cast<char>(std::tolower(c)); }

char UpperCase(char c) { return static_cast<char>(std::toupper(c)); }

bool IsVowel(char c) {
  std::string vowels = std::string("aeiouy");
  return vowels.find(LowerCase(c)) != std::string::npos;
}
}
