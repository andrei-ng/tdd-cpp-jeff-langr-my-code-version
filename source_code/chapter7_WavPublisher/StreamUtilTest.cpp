#include "StreamUtil.h"

#include <fstream>
#include <sstream>

#include "gmock/gmock.h"

TEST(StreamUtil_Size, AnswersNumberOfBytesWrittenToStream) {
   std::istringstream read_from{"abcdefg"};

   ASSERT_EQ(7, stream_util::Size(read_from));
}

