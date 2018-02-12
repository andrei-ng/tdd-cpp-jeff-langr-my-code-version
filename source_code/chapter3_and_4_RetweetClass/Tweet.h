/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

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
