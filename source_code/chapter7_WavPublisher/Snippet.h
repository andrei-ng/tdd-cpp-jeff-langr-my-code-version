#ifndef SNIPPET_H_
#define SNIPPET_H_

#include <memory>
#include <string>

#include "rlog/rlog.h"

#include "FileUtil.h"
#include "WavDescriptor.h"
#include "WavStructs.h"
// to fix the following compiler errors: "error: _rL_60 causes a section type conflict with _rL_35 "rLog(rlog_channel_, ....);
// see https://code.google.com/p/rlog/issues/detail?id=13
#undef RLOG_SECTION
#define RLOG_SECTION

class Snippet {
 public:
  Snippet() {}
  Snippet(std::shared_ptr<FileUtil> file_util, std::shared_ptr<WavDescriptor> descriptor, const std::string& dest,
          rlog::RLogChannel* channel)
      : file_util_(file_util), descriptor_(descriptor), dest_(dest), rlog_channel_(channel) {}

  void WriteWavSnippet(const std::string& name, std::ostream& out, FormatSubchunk& format_subchunk,
                       DataChunk& wav_chunk, char* data) {
    uint32_t seconds_desired{10};
    if (format_subchunk.bits_per_sample == 0) format_subchunk.bits_per_sample = 8;
    uint32_t bytes_per_sample{format_subchunk.bits_per_sample / uint32_t{8}};
    uint32_t samples_to_write{seconds_desired * format_subchunk.samples_per_second};
    uint32_t total_samples{wav_chunk.length / bytes_per_sample};

    samples_to_write = std::min(samples_to_write, total_samples);

    total_seconds_to_write_ = total_samples / format_subchunk.samples_per_second;
    rLog(rlog_channel_, "total seconds %u ", total_seconds_to_write_);

    wav_chunk.length = DataLength(bytes_per_sample, samples_to_write, format_subchunk.channels);
    out.write(reinterpret_cast<char*>(&wav_chunk), sizeof(DataChunk));

    uint32_t starting_sample{total_seconds_to_write_ >= 10 ? 10 * format_subchunk.samples_per_second : 0};
    rLog(rlog_channel_, "writing %u samples", samples_to_write);
    WriteSamples(&out, data, starting_sample, samples_to_write, bytes_per_sample, format_subchunk.channels);
    rLog(rlog_channel_, "completed writing %s", name.c_str());

    long file_size = 0;
    if (file_util_) {
      file_size = file_util_->Size(name);
    }
    descriptor_->Add(dest_, name, total_seconds_to_write_, format_subchunk.samples_per_second, format_subchunk.channels,
                     file_size);
  }

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

  uint32_t total_seconds_to_write_;

 private:
  std::shared_ptr<FileUtil> file_util_;
  std::shared_ptr<WavDescriptor> descriptor_;
  std::string dest_;
  rlog::RLogChannel* rlog_channel_;
};

#endif  //
