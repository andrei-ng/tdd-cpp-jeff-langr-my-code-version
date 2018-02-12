/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#include "string_utilities.h"

#include "char_utilities.h"

namespace stringutils {

std::string HeadLetter(const std::string& word) { return word.substr(0, 1); }

std::string TailLetters(const std::string& word) {
  if (word.length() == 0) return "";
  return word.substr(1);
}

std::string ZeroPad(const std::string& word, const unsigned int target_length) {
  auto zeros_needed = target_length - word.length();
  return word + std::string(zeros_needed, '0');
}

std::string UpperFirst(const std::string& encoding) {
  char first_letter = static_cast<char>(encoding.front());
  return std::string(1, charutils::UpperCase(first_letter));
}
}
