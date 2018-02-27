#ifndef SNIPPET_H_
#define SNIPPET_H_

#include <memory>
#include <string>

#include "rlog/rlog.h"

#include "FileUtil.h"
#include "WavDescriptor.h"

class Snippet {
 public:
  Snippet() {}
  Snippet(std::shared_ptr<FileUtil> file_util, std::shared_ptr<WavDescriptor> descriptor, const std::string& dest,
          rlog::RLogChannel* channel)
      : file_util_(file_util), descriptor_(descriptor), dest_(dest), rlog_channel_(channel) {}

  uint32_t DataLength(const uint32_t bytes_per_sample, const uint32_t samples, const uint32_t channels) const {
    return bytes_per_sample * samples * channels;
  }

  void WriteSamples(std::ostream* out, char* data, const uint32_t starting_sample, const uint32_t samples_to_write,
                    const uint32_t bytes_per_sample, const u_int32_t channels = 1) {
    for (auto sample = starting_sample; sample < starting_sample + samples_to_write; sample++) {
      auto byteOffsetForSample = sample * bytes_per_sample * channels;
      for (uint32_t channel = 0; channel < channels; channel++) {
        auto byteOffsetForChannel = byteOffsetForSample + (channel * bytes_per_sample);
        for (uint32_t byte = 0; byte < bytes_per_sample; byte++) {
          out->put(data[byteOffsetForChannel + byte]);
        }
      }
    }
  }

 private:
  std::shared_ptr<FileUtil> file_util_;
  std::shared_ptr<WavDescriptor> descriptor_;
  std::string dest_;
  rlog::RLogChannel* rlog_channel_;
};

#endif  //
