#ifndef SNIPPET_H_
#define SNIPPET_H_

#include <string>

class Snippet {
 public:
  uint32_t DataLength(const uint32_t bytes_per_sample, const uint32_t samples, const uint32_t channels) const {
    return bytes_per_sample * samples * channels;
  }
};

#endif  //
