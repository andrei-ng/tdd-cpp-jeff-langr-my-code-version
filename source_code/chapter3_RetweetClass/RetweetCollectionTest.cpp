#include "gmock/gmock.h"

#include "RetweetCollection.h"

class ARetweetCollection : public testing::Test {
 public:
  RetweetCollection collection;
};

class ARetweetCollectionWithOneTweet : public testing::Test {
 public:
  RetweetCollection collection;
protected:
  void SetUp() override {
    collection.AddTweet(Tweet());
  }
};

MATCHER_P(HasSize, expected, "") { return arg.Size() == expected && arg.IsEmpty() == (0 == expected); }

TEST_F(ARetweetCollection, IsEmptyWhenCreated) { ASSERT_TRUE(collection.IsEmpty()); }

TEST_F(ARetweetCollectionWithOneTweet, IsNoLongerEmpty) {
  ASSERT_FALSE(collection.IsEmpty());
}

TEST_F(ARetweetCollectionWithOneTweet, HasSizeOfOne) {
  ASSERT_THAT(collection.Size(), ::testing::Eq(1u));
}

TEST_F(ARetweetCollectionWithOneTweet, DecreasesSizeAfterRemovingTweet) {
  collection.RemoveTweet(Tweet());

  ASSERT_THAT(collection, HasSize(0u));
}

/** Alternative for testing connected emptiness/size concepts
 * Do these two tests only once:
 * " [...] The asserts that relate to checking size in these two tests act as precondition assertions. They are
 * technically unnecessary but in this case serve to bolster the relationship between the two concepts. "
*/
TEST_F(ARetweetCollection, IsEmptyWhenItsSizeIsZero) {
  ASSERT_THAT(collection.Size(), ::testing::Eq(0u));
  ASSERT_TRUE(collection.IsEmpty());
}
TEST_F(ARetweetCollection, IsNotEmptyWhenItsSizeIsNonZero) {
  collection.AddTweet(Tweet());
  ASSERT_THAT(collection.Size(), ::testing::Gt(0u));
  ASSERT_FALSE(collection.IsEmpty());
}
/** End special tests case */

TEST_F(ARetweetCollection, IgnoresDuplicateTweetAdded) {
  Tweet a_tweet("msg", "@user");
  Tweet duplicate_tweet(a_tweet);

  collection.AddTweet(a_tweet);
  collection.AddTweet(duplicate_tweet);

  ASSERT_THAT(collection.Size(), ::testing::Eq(1u));
}
