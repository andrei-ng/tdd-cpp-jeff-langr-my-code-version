#include <memory>

#include "gmock/gmock.h"

#include "RetweetCollection.h"

MATCHER_P(HasSize, expected, "") { return arg.Size() == expected && arg.IsEmpty() == (0 == expected); }

class ARetweetCollectionWithOneTweet : public testing::Test {
 public:
  RetweetCollection collection;
  Tweet* a_tweet_;

 protected:
  void SetUp() override {
    a_tweet_ = new Tweet("msg", "@user");
    collection.AddTweet(*a_tweet_);
  }

  void TearDown() override {
    delete a_tweet_;
    a_tweet_ = nullptr;
  }
};

// clang-format off
TEST_F(ARetweetCollectionWithOneTweet, IsNoLongerEmpty) {
 ASSERT_FALSE(collection.IsEmpty());
}

TEST_F(ARetweetCollectionWithOneTweet, HasSizeOfOne) {
 ASSERT_THAT(collection.Size(), ::testing::Eq(1u));
}
// clang-format on

TEST_F(ARetweetCollectionWithOneTweet, DecreasesSizeAfterRemovingTweet) {
  collection.RemoveTweet(*a_tweet_);

  ASSERT_THAT(collection, HasSize(0u));
}

TEST_F(ARetweetCollectionWithOneTweet, IgnoresDuplicateTweetAdded) {
  Tweet duplicate_tweet(*a_tweet_);

  collection.AddTweet(duplicate_tweet);

  ASSERT_THAT(collection.Size(), ::testing::Eq(1u));
}

class ARetweetCollectionWithOneTweet_SmartPtr : public testing::Test {
 public:
  RetweetCollection collection;
  std::shared_ptr<Tweet> a_tweet_;

 protected:
  void SetUp() override {
    a_tweet_ = std::shared_ptr<Tweet>(new Tweet("msg", "@user"));
    collection.AddTweet(*a_tweet_);
  }

  /** No longer need to clean up a_tweet_ */
  //  void TearDown() override {}
};

// clang-format off
TEST_F(ARetweetCollectionWithOneTweet_SmartPtr, IsNoLongerEmpty) {
 ASSERT_FALSE(collection.IsEmpty());
}

TEST_F(ARetweetCollectionWithOneTweet_SmartPtr, HasSizeOfOne) {
 ASSERT_THAT(collection.Size(), ::testing::Eq(1u));
}
// clang-format on

class ARetweetCollection : public testing::Test {
 public:
  RetweetCollection collection;
};

TEST_F(ARetweetCollection, IsEmptyWhenCreated) { ASSERT_TRUE(collection.IsEmpty()); }

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

TEST_F(ARetweetCollection, IncrementsSizeWhenTweetsAdded) {
  Tweet first("msg1", "@user");
  collection.AddTweet(first);
  Tweet second("msg2", "@user");
  collection.AddTweet(second);

  ASSERT_THAT(collection.Size(), ::testing::Eq(2u));
}
