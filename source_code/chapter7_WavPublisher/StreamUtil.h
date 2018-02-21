/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#ifndef STREAM_UTIL_H_
#define STREAM_UTIL_H_

#include <ios>
#include <istream>

namespace stream_util {
std::streamsize Size(std::istream& stream);
}
#endif  // STREAM_UTIL_H_
