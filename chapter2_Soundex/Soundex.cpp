#include "Soundex.h"

static const size_t kMaxCodeLength{4};
static const std::string kNotADigit{"*"};

std::string Soundex::EncodeDigit(char letter) const {
  const std::map<char, std::string> encodings{{'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"}, {'c', "2"}, {'g', "2"},
                                              {'j', "2"}, {'k', "2"}, {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"},
                                              {'d', "3"}, {'t', "3"}, {'l', "4"}, {'m', "5"}, {'n', "5"}, {'r', "6"}};

  auto it = encodings.find(letter);
  if (it == encodings.end()) {
    return kNotADigit;
  } else {
    return it->second;
  }
}

std::string Soundex::Encode(const std::string& word) const {
  return ZeroPad(UpperFirst(Head(word)) + EncodeToDigits(Tail(word)));
}

std::string Soundex::ZeroPad(const std::string& word) const {
  size_t max_encoding_length{4};
  max_encoding_length = std::min(word.length(), max_encoding_length);
  auto zeros_needed = kMaxCodeLength - max_encoding_length;
  return word + std::string(zeros_needed, '0');
}

std::string Soundex::UpperFirst(const std::string& encoding) const {
  unsigned char first_letter = static_cast<unsigned char>(encoding.front());
  return std::string(1, static_cast<char>(std::toupper(first_letter)));
}

std::string Soundex::Head(const std::string& word) const { return word.substr(0, 1); }

std::string Soundex::Tail(const std::string& word) const { return word.substr(1, std::string::npos); }

std::string Soundex::EncodeToDigits(const std::string& word) const {
  std::string encoding;
  for (auto letter : word) {
    if (IsCompleteEncoding(encoding)) {
      break;
    }
    auto digit_encoding = EncodeDigit(letter);
    if (IsValidEncoding(digit_encoding) && digit_encoding != GetLastEncodedDigit(encoding)) {
      encoding += EncodeDigit(letter);
    }
  }
  return encoding;
}

std::string Soundex::GetLastEncodedDigit(const std::string& encoding) const {
  if (encoding.empty()) {
    return kNotADigit;
  } else {
    return std::string(1, encoding.back());
  }
}

bool Soundex::IsCompleteEncoding(const std::string& encoding) const { return encoding.length() == kMaxCodeLength - 1; }

bool Soundex::IsValidEncoding(const std::string& encoding) const { return encoding != kNotADigit; }
