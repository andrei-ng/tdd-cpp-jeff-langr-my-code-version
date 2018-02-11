#include "char_utilities.h"

namespace charutils {
char LowerCase(char c) { return static_cast<char>(std::tolower(c)); }

char UpperCase(char c) { return static_cast<char>(std::toupper(c)); }

bool IsVowel(char c) {
  std::string vowels = std::string("aeiouy");
  return vowels.find(LowerCase(c)) != std::string::npos;
}
}
