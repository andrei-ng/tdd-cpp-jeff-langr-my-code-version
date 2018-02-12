/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#ifndef TDD_CH5_HTTP_H_
#define TDD_CH5_HTTP_H_

#include <string>

class Http {
 public:
  virtual ~Http() {}
  virtual void Initialize() = 0;
  virtual std::string Get(const std::string& url) const = 0;
};

#endif  // TDD_CH5_HTTP_H_
