/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#include "Tweet.h"
#include "gmock/gmock.h"

TEST(ATweet, UserDefaultsToNullWhenNotProvided) {
  Tweet tweet("msg");

  ASSERT_THAT(tweet.GetUser(), ::testing::Eq("@null"));
}

TEST(ATweet, IsEqualToAnotherWhenMessageAndUserAreEqual) {
  Tweet a("msg", "@user");
  Tweet b("msg", "@user");

  ASSERT_THAT(a, ::testing::Eq(b));
}

TEST(ATweet, IsNotEqualToAnotherWhenMessagesAreUnequal) {
  Tweet a("msgX", "@user");
  Tweet b("msgY", "@user");

  ASSERT_THAT(a, ::testing::Ne(b));
}

TEST(ATweet, IsNotEqualToAnotherWhenUsersAreUnequal) {
  Tweet a("msg", "@user1");
  Tweet b("msg", "@user2");

  ASSERT_THAT(a, ::testing::Ne(b));
}

TEST(ATweet, IsLessThanWhenMessagesAreEqualAndUserIsLessThan) {
  Tweet a("msg", "@user1");
  Tweet b("msg", "@user2");

  ASSERT_THAT(a, ::testing::Lt(b));
}

TEST(ATweet, IsLessThanWhenUserEqualAndMessageIsLessThan) {
  Tweet a("msgA", "@user");
  Tweet b("msgB", "@user");

  ASSERT_THAT(a, ::testing::Lt(b));
}

TEST(ATweet, CanBeCopyConstructed) {
  Tweet a("msgA", "@user");
  Tweet b(a);

  ASSERT_THAT(a, ::testing::Eq(b));
}

class ATweetWithInvalidUser : public testing::Test {
 protected:
  void SetUp() override { invalid_user = std::string("notStartingWith@"); }
  std::string invalid_user;
};

TEST_F(ATweetWithInvalidUser, RequiresUserToStartWithAnAtSign) { ASSERT_ANY_THROW(Tweet tweet("msg", invalid_user)); }

TEST_F(ATweetWithInvalidUser, RequiresUserToStartWithAnAtSignToBeValidUser) {
  ASSERT_THROW(Tweet tweet("msg", invalid_user), InvalidUserException);
}

TEST_F(ATweetWithInvalidUser, RequiresUserNameToStartWithAnAtSign_v3) {
  try {
    Tweet tweet("msg", invalid_user);
    FAIL();
  } catch (const InvalidUserException& /*expected*/) {
  }
}

TEST_F(ATweetWithInvalidUser, RequiresUserNameToStartWithAtSignThrowsInvalidUserMessage) {
  try {
    Tweet tweet("msg", invalid_user);
    FAIL();
  } catch (const InvalidUserException& expected) {
    ASSERT_STREQ("Invalid argument 'user': notStartingWith@", expected.what());
  }
}
