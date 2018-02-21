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
#include <sstream>
#include <string>

#include "gmock/gmock.h"

using namespace testing;

class WavReader_WriteSamples : public ::testing::Test {
 public:
  WavReader reader{".", "."};
  std::ostringstream out;
};

TEST_F(WavReader_WriteSamples, WritesSingleSample) {
  char data[] = "abcd";
  uint32_t bytesPerSample{1};
  uint32_t startingSample{0};
  uint32_t samplesToWrite{1};

  reader.WriteSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

  ASSERT_EQ(out.str(), "a");
}

TEST_F(WavReader_WriteSamples, WritesMultibyteSampleFromMiddle) {
  char data[] = "0123456789ABCDEFG";  // just keeping this type of initialization for example purposes
  uint32_t bytesPerSample{2};
  uint32_t startingSample{4};
  uint32_t samplesToWrite{3};

  reader.WriteSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

  ASSERT_EQ("89ABCD", out.str());
}
