/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#ifndef SOUNDEX_STRING_UTILS_H_
#define SOUNDEX_STRING_UTILS_H_

#include <string>

namespace stringutils {
std::string ZeroPad(const std::string& word, unsigned int target_length);

std::string UpperFirst(const std::string& encoding);

std::string HeadLetter(const std::string& word);

std::string TailLetters(const std::string& word);
}

#endif  // SOUNDEX_STRING_UTILS_H_
