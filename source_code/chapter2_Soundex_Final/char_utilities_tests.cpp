/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

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
