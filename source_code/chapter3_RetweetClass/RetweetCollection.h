#ifndef TDD_CH3_RETWEETCOLLECTION_H_
#define TDD_CH3_RETWEETCOLLECTION_H_

#include "Tweet.h"

class RetweetCollection {
 public:
  RetweetCollection() : size_(0) {}
  bool IsEmpty() const { return 0 == Size(); }

  unsigned int Size() const { return size_; }

  void AddTweet(const Tweet & /*tweet*/) { size_ += 1; }

 private:
  unsigned int size_;
};
#endif  // TDD_CH3_RETWEETCOLLECTION_H_
