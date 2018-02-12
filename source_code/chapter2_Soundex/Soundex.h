/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#ifndef CPP_TDD_CHAPTER2_SOUNDEX_H_
#define CPP_TDD_CHAPTER2_SOUNDEX_H_

#include <iostream>
#include <map>
#include <string>

class Soundex {
 public:
  std::string EncodeDigit(char letter) const;

  /** Made public for Test-Driving */
  std::string Encode(const std::string& word) const;

 private:
  void EncodeHead(std::string& encoding, const std::string& word) const;

  void EncodeTail(std::string& encoding, const std::string& word) const;

  void EncodeLetter(std::string& encoding, char letter, char last_letter) const;

  std::string ZeroPad(const std::string& word) const;

  std::string UpperFirst(const std::string& encoding) const;

  std::string HeadLetter(const std::string& word) const;

  std::string TailLetters(const std::string& word) const;

  std::string EncodeToDigits(const std::string& word) const;

  std::string GetLastEncodedDigit(const std::string& encoding) const;

  bool IsCompleteEncoding(const std::string& encoding) const;

  bool IsValidEncoding(const std::string& encoding) const;

  char LowerCase(char c) const;

  bool IsVowel(char c) const;
};

#endif  // CPP_TDD_CHAPTER2_SOUNDEX_H_
