#ifndef TDD_CH3_TWEET_H_
#define TDD_CH3_TWEET_H_

#include <string>

class Tweet {
 public:
  Tweet(const std::string& message = "", const std::string& user = "") : message_(message), user_(user) {}

  /** Don't seem to be needed by the <set> template class on Tweet type. Only the less operator is required */
  //  bool operator==(const Tweet& rhs) const { return (message_ == rhs.message_ && user_ == rhs.user_); }
  //  bool operator!=(const Tweet& rhs) const { return !(*this == rhs); }

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
