#include "Soundex.h"

#include "gmock/gmock.h"

class SoundexEncoding : public testing::Test {
 public:
  Soundex soundex;
};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) { ASSERT_THAT(soundex.Encode("A"), testing::Eq("A000")); }

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) { ASSERT_THAT(soundex.Encode("I"), testing::Eq("I000")); }

TEST_F(SoundexEncoding, ReplaceConsonantsWithAppropriateDigitCode) {
  ASSERT_THAT(soundex.Encode("Al"), testing::Eq("A400"));
}

TEST_F(SoundexEncoding, IgnoreNonAlphabetics) { ASSERT_THAT(soundex.Encode("A#"), testing::Eq("A000")); }

TEST_F(SoundexEncoding, IgnoreVowels) { ASSERT_THAT(soundex.Encode("Ao"), testing::Eq("A000")); }

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits) {
  ASSERT_THAT(soundex.Encode("Acdl"), testing::Eq("A234"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters) {
  ASSERT_THAT(soundex.Encode("Dcdlb").length(), testing::Eq(4u));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings) {
  // Extra steps to clarify the same encoding for same type of consonants
  ASSERT_THAT(soundex.EncodeDigit('b'), soundex.EncodeDigit('f'));
  ASSERT_THAT(soundex.EncodeDigit('c'), soundex.EncodeDigit('g'));
  ASSERT_THAT(soundex.EncodeDigit('d'), soundex.EncodeDigit('t'));

  ASSERT_THAT(soundex.Encode("Abfcgdt"), testing::Eq("A123"));
}

TEST_F(SoundexEncoding, UppercasingTheFirstLetterInTheEncoding) {
  ASSERT_THAT(soundex.Encode("abcd"), testing::StartsWith("A"));
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters) {
  ASSERT_THAT(soundex.Encode("BaAeEiIoOuUhHyYcdl"), testing::Eq("B234"));
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants) {
  ASSERT_THAT(soundex.Encode("BCDL"), testing::Eq(soundex.Encode("Bcdl")));
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st) {
  ASSERT_THAT(soundex.Encode("Bbcd"), testing::Eq("B230"));
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeparatedByVowels) {
  ASSERT_THAT(soundex.Encode("Jbob"), testing::Eq("J110"));
}
