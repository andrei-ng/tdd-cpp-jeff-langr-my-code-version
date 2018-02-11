#include "gmock/gmock.h"

#include "RetweetCollection.h"

class ARetweetCollection : public testing::Test {
 public:
  RetweetCollection collection;
};

TEST_F(ARetweetCollection, IsEmptyWhenCreated) { ASSERT_TRUE(collection.IsEmpty()); }

TEST_F(ARetweetCollection, HasSizeZeroWhenCreated) { ASSERT_THAT(collection.Size(), ::testing::Eq(0u)); }

TEST_F(ARetweetCollection, IsNoLongerEmptyAfterTweetAdded) {
  collection.AddTweet(Tweet());
  ASSERT_FALSE(collection.IsEmpty());
}

TEST_F(ARetweetCollection, HasSizeOfOneAfterTweetAdded) {
  collection.AddTweet(Tweet());
  ASSERT_THAT(collection.Size(), ::testing::Eq(1u));
}
