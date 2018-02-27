/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#include "Snippet.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "gmock/gmock.h"

#include "FileUtil.h"

using namespace testing;

class WavSnippet_WriteSamples : public ::testing::Test {
 public:
  Snippet snippet;
  std::ostringstream out;
};

TEST_F(WavSnippet_WriteSamples, WritesSingleSample) {
  char data[] = "abcd";
  uint32_t bytes_per_sample{1};
  uint32_t starting_sample{0};
  uint32_t samples_to_write{1};

  snippet.WriteSamples(&out, data, starting_sample, samples_to_write, bytes_per_sample);

  ASSERT_EQ(out.str(), "a");
}

TEST_F(WavSnippet_WriteSamples, WritesMultibyteSampleFromMiddle) {
  char data[]{"0123456789ABCDEFG"};  // just keeping this type of initialization for example purposes
  uint32_t bytes_per_sample{2};
  uint32_t starting_sample{4};
  uint32_t samples_to_write{3};

  snippet.WriteSamples(&out, data, starting_sample, samples_to_write, bytes_per_sample);

  ASSERT_EQ("89ABCD", out.str());
}

TEST_F(WavSnippet_WriteSamples, IncorporatesChannelCount) {
  char data[]{"0123456789ABCDEFG"};
  uint32_t bytes_per_sample{2};
  uint32_t starting_sample{0};
  uint32_t samples_to_write{2};
  uint32_t channels{2};

  snippet.WriteSamples(&out, data, starting_sample, samples_to_write, bytes_per_sample, channels);

  ASSERT_EQ("01234567", out.str());
}

class WavSnippet_DataLength : public ::testing::Test {
 public:
  Snippet snippet;
};

TEST_F(WavSnippet_DataLength, IsProductOfChannels_bytes_per_sample_and_Samples) {
  uint32_t bytes_per_sample{2};
  uint32_t samples{5};
  uint32_t channels{4};

  uint32_t length = snippet.DataLength(bytes_per_sample, samples, channels);

  ASSERT_EQ(2 * 5 * 4, length);
}

class MockWavDescriptor : public WavDescriptor {
 public:
  MockWavDescriptor() : WavDescriptor("") {}
  MOCK_METHOD6(Add, void(const std::string&, const std::string&, uint32_t total_seconds, uint32_t, uint32_t,
                         long file_size));
};

class MockFileUtil : public FileUtil {
 public:
  MockFileUtil() : FileUtil() {}
  MOCK_METHOD1(Size, std::streamsize(const std::string& name));
};

class WavSnippet_WriteSnippetWithMock : public ::testing::Test {
 public:
  //  std::shared_ptr<MockWavDescriptor> descriptor{new MockWavDescriptor};
  std::shared_ptr<MockWavDescriptor> descriptor = std::make_shared<MockWavDescriptor>();
  std::shared_ptr<MockFileUtil> file_util = std::make_shared<MockFileUtil>();
  rlog::RLogChannel* channel{0};

  Snippet snippet;
  std::istringstream input{""};
  std::ostringstream output;
  FormatSubchunk format_subchunk;
  DataChunk data_chunk;
  uint32_t num_bytes_in_chunk = 8;  // number of bytes
  uint32_t number_of_bits_in_two_bytes{2 * 8};
  unsigned int arbitrary_file_size{5};
  char* data;

  void SetUp() override {
    data = new char[4];
    data_chunk.length = num_bytes_in_chunk;
    format_subchunk.bits_per_sample = static_cast<unsigned short>(number_of_bits_in_two_bytes);
    format_subchunk.samples_per_second = 1;

    snippet = Snippet(file_util, descriptor, "", channel);
  }

  void TearDown() override { delete[] data; }
};


TEST_F(WavSnippet_WriteSnippetWithMock, SendTotalSecondsToDescriptor) {
  uint32_t num_samples_per_second =
      num_bytes_in_chunk / (number_of_bits_in_two_bytes / 8 / format_subchunk.samples_per_second);

  EXPECT_CALL(*file_util, Size(_)).Times(1).WillOnce(Return(0));
  EXPECT_CALL(*descriptor, Add(_, _, num_samples_per_second, _, _, _)).Times(1);
  snippet.WriteWavSnippet("any", output, format_subchunk, data_chunk, data);

  ASSERT_EQ(num_samples_per_second, snippet.total_seconds_to_write_);
}

TEST_F(WavSnippet_WriteSnippetWithMock, SendsFileLengthAndTotalSecondsToDescriptor) {
  uint32_t num_samples_per_second =
      num_bytes_in_chunk / (number_of_bits_in_two_bytes / 8 / format_subchunk.samples_per_second);

  EXPECT_CALL(*file_util, Size(_)).Times(1).WillOnce(Return(arbitrary_file_size));
  EXPECT_CALL(*descriptor, Add(_, _, num_samples_per_second, _, _, arbitrary_file_size)).Times(1);
  snippet.WriteWavSnippet("any", output, format_subchunk, data_chunk, data);

  ASSERT_EQ(num_samples_per_second, snippet.total_seconds_to_write_);
}

