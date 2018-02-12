/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#ifndef SOUNDEX_CHAR_UTILS_H_
#define SOUNDEX_CHAR_UTILS_H_

#include <string>

namespace charutils {
char LowerCase(char c);

char UpperCase(char c);

bool IsVowel(char c);
}

#endif  // SOUNDEX_CHAR_UTILS_H_
