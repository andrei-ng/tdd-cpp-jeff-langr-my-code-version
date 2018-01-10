#include "Soundex.h"

#include "gmock/gmock.h"

class SoundexEncoding : public testing::Test {
 public:
    Soundex soundex;
};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
    ASSERT_THAT(soundex.Encode("A"), testing::Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
    ASSERT_THAT(soundex.Encode("I"), testing::Eq("I000"));
}

TEST_F(SoundexEncoding, ReplaceConsonantsWithAppropriateDigitCode) {
    ASSERT_THAT(soundex.Encode("Al"), testing::Eq("A400"));
}

TEST_F(SoundexEncoding, IgnoreNonAlphabeticsOrVowels) {
    ASSERT_THAT(soundex.Encode("A#"), testing::Eq("A000"));
}
