#include "gmock/gmock.h"
#include "Tweet.h"

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
  void SetUp() override {
    invalid_user = std::string("notStartingWith@");
  }
  std::string invalid_user;
};

TEST_F(ATweetWithInvalidUser, RequiresUserToStartWithAnAtSign) {
   ASSERT_ANY_THROW(Tweet tweet("msg", invalid_user));
}

TEST_F(ATweetWithInvalidUser, RequiresUserToStartWithAnAtSignToBeValidUser) {
   ASSERT_THROW(Tweet tweet("msg", invalid_user), InvalidUserException);
}

TEST_F(ATweetWithInvalidUser, RequiresUserNameToStartWithAnAtSign_v3) {
   std::string invalidUser("notStartingWith@");
   try {
      Tweet tweet("msg", invalidUser);
      FAIL();
   }
   catch (const InvalidUserException& /*expected*/) {}
}
