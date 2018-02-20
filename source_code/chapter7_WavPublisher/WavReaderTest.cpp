/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#include "WavReader.h"

#include <iostream>
#include <string>

#include "gmock/gmock.h"

using namespace testing;

class AWavReader : public ::testing::Test {};

TEST_F(AWavReader, FileHasExtension) {
  std::string s{"a.bcd"};
  ASSERT_TRUE(!HasExtension(s, "xxxx"));
  ASSERT_TRUE(HasExtension(s, "bcd"));
  std::string bigger{"aaabcd"};
  ASSERT_TRUE(!HasExtension(s, bigger));
}
