/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#include "gmock/gmock.h"

#include "string_utilities.h"

using namespace testing;

TEST(StringUtils, AnswersHeadAsItsFirstLetter) {
   ASSERT_THAT(stringutils::HeadLetter("ghe"), Eq("g"));
}

TEST(StringUtils, AnswersHeadAsEmptyWhenEmpty) {
   ASSERT_THAT(stringutils::HeadLetter(""), Eq(""));
}

TEST(StringUtils, AnswersTailAsAllLettersAfterHead) {
   ASSERT_THAT(stringutils::TailLetters("ghe"), Eq("he"));
}

TEST(StringUtils, AnswersTailAsEmptyWhenEmpty) {
   ASSERT_THAT(stringutils::TailLetters(""), Eq(""));
}

TEST(StringUtils, AnswersTailAsEmptyWhenContainsOnlyOneCharacter) {
   ASSERT_THAT(stringutils::TailLetters("G"), Eq(""));
}

TEST(StringUtils, ZeroPaddingWord) {
   ASSERT_THAT(stringutils::ZeroPad("G", 3), Eq("G00"));
}
