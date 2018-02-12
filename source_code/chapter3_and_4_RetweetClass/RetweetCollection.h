/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#ifndef TDD_CH3_RETWEETCOLLECTION_H_
#define TDD_CH3_RETWEETCOLLECTION_H_

#include <iostream>
#include <set>

#include "Tweet.h"

class RetweetCollection {
 public:
  bool IsEmpty() const { return 0 == Size(); }

  unsigned long Size() const { return tweets_.size(); }

  void AddTweet(const Tweet& tweet) { tweets_.insert(tweet); }
  void RemoveTweet(const Tweet& tweet) { tweets_.erase(tweets_.find(tweet)); }

 private:
  std::set<Tweet> tweets_;
};
#endif  // TDD_CH3_RETWEETCOLLECTION_H_
