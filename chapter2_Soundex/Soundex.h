#ifndef CPP_TDD_CHAPTER2_SOUNDEX_H_
#define CPP_TDD_CHAPTER2_SOUNDEX_H_

#include <string>
#include <map>
#include <iostream>

class Soundex {
 public:
    std::string EncodeDigit(char letter) const {
        const std::map<char, std::string> encodings {
            {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
            {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"},
            {'s', "2"}, {'x', "2"}, {'z', "2"},
            {'d', "3"}, {'t', "3"},
            {'l', "4"},
            {'m', "5"}, {'n', "5"},
            {'r', "6"}
        };

        auto it = encodings.find(letter);
        if (it == encodings.end()) {
            return kNotADigit;
        } else {
            return it->second;
        }
    }

    std::string Encode(const std::string & word) const {
        return ZeroPad(UpperFirst(Head(word)) + EncodeToDigits(Tail(word)));
    }

    const size_t kMaxCodeLength{4};
    const std::string kNotADigit{"*"};

 private:
    std::string ZeroPad(const std::string & word) const {
        size_t max_encoding_length{4};
        max_encoding_length = std::min(word.length(), max_encoding_length);
        auto zeros_needed = kMaxCodeLength - max_encoding_length;
        return word + std::string(zeros_needed, '0');
    }

    std::string UpperFirst(const std::string& encoding) const {
        unsigned char first_letter = static_cast<unsigned char>(encoding.front());
        return std::string(1, std::toupper(first_letter));
    }

    std::string Head(const std::string & word) const {
        return word.substr(0, 1);
    }

    std::string Tail(const std::string& word) const {
        return word.substr(1, std::string::npos);
    }

    std::string EncodeToDigits(const std::string & word) const {
        std::string encoding;
        for (auto letter: word) {
            if (IsCompleteEncoding(encoding)) {
                break;
            }
            auto digit_encoding = EncodeDigit(letter);
            if ( IsValidEncoding(digit_encoding) &&  digit_encoding!= GetLastEncodedDigit(encoding)) {
                encoding += EncodeDigit(letter);
            }
        }
        return encoding;
    }

    std::string GetLastEncodedDigit(const std::string& encoding) const {
        if (encoding.empty()) {
            return kNotADigit;
        } else {
            return std::string(1, encoding.back());
        }
    }

    bool IsCompleteEncoding(const std::string & encoding) const {
        return encoding.length() == kMaxCodeLength - 1;
    }

    bool IsValidEncoding(const std::string& encoding) const {
        return encoding != kNotADigit;
    }
};

#endif //CPP_TDD_CHAPTER2_SOUNDEX_H_
