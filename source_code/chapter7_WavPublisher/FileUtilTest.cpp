/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#include "FileUtil.h"

#include <stdio.h>
#include <fstream>
#include <istream>

#include <string>

#include "gmock/gmock.h"

#include "StreamUtil.h"

using namespace testing;

class FileUtilTests : public ::testing::Test {
 public:
  const std::string temp_file_name{"FileUtil_SizeTest.dat"};

  FileUtil util;

  void TearDown() { remove(temp_file_name.c_str()); }

  virtual void CreateTempFile(const std::string& content) {
    std::ofstream stream{temp_file_name, std::ios::out | std::ios::binary};
    stream << content << std::endl;
    stream.close();
  }
};

/** slow tests that must interact with the filesystem */
class FileUtil_SlowTests_Size : public FileUtilTests {};
class FileUtil_SlowTests_Execute : public FileUtilTests {};

TEST_F(FileUtil_SlowTests_Size, AnswersFileContentSize) {
  std::string content("12345");
  CreateTempFile(content);

  size_t expected_size{content.length() + sizeof('\0')};
  EXPECT_EQ(expected_size, util.Size(temp_file_name));
}

TEST_F(FileUtil_SlowTests_Execute, IsPassedStreamFromFile) {
  std::string content("abcdefg");
  std::string buffer;
  std::streamsize returnValue{999};

  /** My first encounter with a C++ lambda function */
  auto func = [&](std::istream& stream) {
    getline(stream, buffer);
    return returnValue;
  };

  CreateTempFile(content);

  auto result = util.ExecuteFunctionOnStream(temp_file_name, func);

  EXPECT_EQ(returnValue, result);
  ASSERT_EQ(content, buffer);
}

TEST_F(FileUtil_SlowTests_Execute, DemonstratedWithStreamUtilSizeFunction) {
  std::string content("abcdefg");
  CreateTempFile(content);

   /** My Second encounter with a C++ lambda function :)) */
  std::streamsize size = util.ExecuteFunctionOnStream(temp_file_name, [&](std::istream& s) { return stream_util::Size(s); });
  /** Above call is identical to ...*/
  /*
  auto func = [&](std::istream& stream) {
    return stream_util::Size(stream);
  };
  std::streamsize size = util.ExecuteFunctionOnStream(temp_file_name, func);
  */

  EXPECT_EQ(content.length() + sizeof('\0'), size);
}
