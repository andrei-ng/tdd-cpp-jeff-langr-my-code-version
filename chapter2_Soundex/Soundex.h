#ifndef CPP_TDD_CHAPTER2_SOUNDEX_H_
#define CPP_TDD_CHAPTER2_SOUNDEX_H_

#include <iostream>
#include <map>
#include <string>

class Soundex {
 public:
  std::string EncodeDigit(char letter) const;

  std::string Encode(const std::string& word) const;

 private:
  std::string ZeroPad(const std::string& word) const;

  std::string UpperFirst(const std::string& encoding) const;

  std::string Head(const std::string& word) const;

  std::string Tail(const std::string& word) const;

  std::string EncodeToDigits(const std::string& word) const;

  std::string GetLastEncodedDigit(const std::string& encoding) const;
  bool IsCompleteEncoding(const std::string& encoding) const;

  bool IsValidEncoding(const std::string& encoding) const;
};

#endif  // CPP_TDD_CHAPTER2_SOUNDEX_H_
