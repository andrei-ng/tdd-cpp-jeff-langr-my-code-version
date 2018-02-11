#ifndef TDD_CH3_TWEET_H_
#define TDD_CH3_TWEET_H_

#include <string>

class Tweet {
 public:
  static const std::string NULL_USER;

  Tweet(const std::string& message = "", const std::string& user = Tweet::NULL_USER) : message_(message), user_(user) {}

  bool IsValidUser(const std::string& user) const { return '@' == user[0]; }

  std::string GetUser() const { return user_; }

  bool operator==(const Tweet& rhs) const { return (message_ == rhs.message_ && user_ == rhs.user_); }
  bool operator!=(const Tweet& rhs) const { return !(*this == rhs); }

  bool operator<(const Tweet& rhs) const {
    if (user_ == rhs.user_) {
      return message_ < rhs.message_;
    }

    return user_ < rhs.user_;
  }

 private:
  std::string message_;
  std::string user_;
};

#endif  // TDD_CH3_TWEET_H_
