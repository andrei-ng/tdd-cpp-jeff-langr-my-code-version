#ifndef CPP_TDD_CHAPTER2_SOUNDEX_H_
#define CPP_TDD_CHAPTER2_SOUNDEX_H_

#include <string>
#include <map>

class Soundex {
 public:
    std::string Encode(const std::string & word) const {
        return ZeroPad(Head(word) + EncodeToDigits(word));
    }

    const size_t kMaxCodeLength{4};

 private:
    std::string ZeroPad(const std::string & word) const {
        auto zeros_needed = kMaxCodeLength - word.length();

        return word + std::string(zeros_needed, '0');
    }

    std::string Head(const std::string & word) const {
        return word.substr(0, 1);
    }

    std::string EncodeToDigits(const std::string & word) const {
        if (word.length() > 1) {
            return EncodeDigit(word[1]);
        } else {
            return "";
        }
    }

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
            return "";
        } else {
            return it->second;
        }
    }
};

#endif //CPP_TDD_CHAPTER2_SOUNDEX_H_
