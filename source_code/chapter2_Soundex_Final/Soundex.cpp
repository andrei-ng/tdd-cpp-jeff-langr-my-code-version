/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#include "Soundex.h"

#include "string_utilities.h"
#include "char_utilities.h"

std::string Soundex::Encode(const std::string& word) const {
  return stringutils::ZeroPad(stringutils::UpperFirst(stringutils::HeadLetter(word)) +
                              stringutils::TailLetters(EncodeToDigits(word)), kMaxCodeLength);
}

std::string Soundex::EncodeToDigits(const std::string& word) const {
  std::string encoding;

  EncodeHead(encoding, word);
  EncodeTail(encoding, word);

  return encoding;
}

void Soundex::EncodeHead(std::string& encoding, const std::string& word) const {
  /** encode first letter to be able to compare the second letter against it */
  char previous_letter = '\0';  // no previous letter: empty character
  EncodeLetter(encoding, word.front(), previous_letter);
}

void Soundex::EncodeTail(std::string& encoding, const std::string& word) const {
  for (auto i = 1u; i < word.length(); i++) {
    if (IsCompleteEncoding(encoding)) {
      break;
    }
    EncodeLetter(encoding, word[i], word[i - 1]);
  }
}

bool Soundex::IsCompleteEncoding(const std::string& encoding) const { return encoding.length() == kMaxCodeLength; }

void Soundex::EncodeLetter(std::string& encoding, char letter, char last_letter) const {
  bool is_encoding_of_first_letter = (encoding.length() == 0);
  auto digit_encoding = EncodeToDigit(letter);
  if ((is_encoding_of_first_letter) ||
      (IsValidEncoding(digit_encoding) && (digit_encoding != GetLastEncodedDigit(encoding) || charutils::IsVowel(last_letter)))) {
    encoding += digit_encoding;
  }
}

bool Soundex::IsValidEncoding(const std::string& encoding) const { return encoding != kNotADigit; }

std::string Soundex::GetLastEncodedDigit(const std::string& encoding) const {
  if (encoding.empty()) {
    return kNotADigit;
  } else {
    return std::string(1, encoding.back());
  }
}

std::string Soundex::EncodeToDigit(char letter) const {
  const std::map<char, std::string> encodings{{'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"}, {'c', "2"}, {'g', "2"},
                                              {'j', "2"}, {'k', "2"}, {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"},
                                              {'d', "3"}, {'t', "3"}, {'l', "4"}, {'m', "5"}, {'n', "5"}, {'r', "6"}};

  auto it = encodings.find(charutils::LowerCase(letter));
  if (it == encodings.end()) {
    return kNotADigit;
  } else {
    return it->second;
  }
}
