#include "gmock/gmock.h"

#include "char_utilities.h"

using namespace testing;

TEST(CharUtils, IsAVowelForSixSpecificLetters) {
   ASSERT_TRUE(charutils::IsVowel('A'));
   ASSERT_TRUE(charutils::IsVowel('E'));
   ASSERT_TRUE(charutils::IsVowel('I'));
   ASSERT_TRUE(charutils::IsVowel('O'));
   ASSERT_TRUE(charutils::IsVowel('U'));
   ASSERT_TRUE(charutils::IsVowel('Y'));
}

TEST(CharUtils, IsAVowelForLowercaseLetters) {
   ASSERT_TRUE(charutils::IsVowel('a'));
   ASSERT_TRUE(charutils::IsVowel('e'));
   ASSERT_TRUE(charutils::IsVowel('i'));
   ASSERT_TRUE(charutils::IsVowel('o'));
   ASSERT_TRUE(charutils::IsVowel('u'));
   ASSERT_TRUE(charutils::IsVowel('y'));
}

TEST(CharUtils, IsNotAVowelForAnyOtherCharacter) {
   ASSERT_FALSE(charutils::IsVowel('c'));
}

TEST(CharUtils, AnswersAppropriateUpperCaseLetter) {
   ASSERT_THAT(charutils::UpperCase('g'), Eq('G'));
}

TEST(CharUtils, HandlesAlreadyUppercasedLetters) {
   ASSERT_THAT(charutils::UpperCase('A'), Eq('A'));
}

TEST(CharUtils, IgnoresNonLettersWhenUppercasing) {
   ASSERT_THAT(charutils::UpperCase('*'), Eq('*'));
}

TEST(CharUtils, AnswersAppropriateLowerCaseLetter) {
   ASSERT_THAT(charutils::LowerCase('O'), Eq('o'));
}

TEST(CharUtils, HandlesAlreadyLowercased) {
   ASSERT_THAT(charutils::LowerCase('b'), Eq('b'));
}

TEST(CharUtils, IgnoresNonLettersWhenLowercasing) {
   ASSERT_THAT(charutils::LowerCase('-'), Eq('-'));
}
