/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

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
  ASSERT_THAT(soundex.EncodeToDigit('b'), soundex.EncodeToDigit('f'));
  ASSERT_THAT(soundex.EncodeToDigit('c'), soundex.EncodeToDigit('g'));
  ASSERT_THAT(soundex.EncodeToDigit('d'), soundex.EncodeToDigit('t'));

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
