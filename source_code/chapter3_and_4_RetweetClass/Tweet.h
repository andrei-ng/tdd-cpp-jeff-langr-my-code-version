#ifndef TDD_CH3_TWEET_H_
#define TDD_CH3_TWEET_H_

#include <stdexcept>
#include <string>
#include <iostream>

class InvalidUserException : public std::invalid_argument {
 public:
  InvalidUserException(const std::string& user)
      : invalid_argument("Invalid argument 'user': " + user) {}
};

class Tweet {
 public:
  static const std::string NULL_USER;

  Tweet(const std::string& message = "", const std::string& user = Tweet::NULL_USER) : message_(message), user_(user) {
    if (!IsValidUser(user_)) throw InvalidUserException(user_);
  }

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
