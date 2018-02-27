/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#ifndef WAVSTRUCTS_H_
#define WAVSTRUCTS_H_

#include <stdint.h>

struct FormatSubchunk {
  uint16_t format_tag;
  uint16_t channels;
  uint32_t samples_per_second;
  uint32_t average_bytes_per_second;
  uint16_t block_align;
  uint16_t bits_per_sample;
};

struct DataChunk {
  uint32_t length;
};

#endif
