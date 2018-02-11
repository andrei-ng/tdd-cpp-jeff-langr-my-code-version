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
