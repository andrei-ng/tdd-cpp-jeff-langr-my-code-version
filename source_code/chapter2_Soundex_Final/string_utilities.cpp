#include "string_utilities.h"

#include "char_utilities.h"

namespace stringutils {

std::string HeadLetter(const std::string& word) { return word.substr(0, 1); }

std::string TailLetters(const std::string& word) { return word.substr(1, std::string::npos); }

std::string ZeroPad(const std::string& word, const unsigned int target_length) {
  auto zeros_needed = target_length - word.length();
  return word + std::string(zeros_needed, '0');
}

std::string UpperFirst(const std::string& encoding) {
  char first_letter = static_cast<char>(encoding.front());
  return std::string(1, charutils::UpperCase(first_letter));
}
}
