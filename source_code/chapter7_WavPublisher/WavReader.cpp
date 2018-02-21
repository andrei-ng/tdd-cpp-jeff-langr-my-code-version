/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#include "WavReader.h"
#include "WavDescriptor.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>

#include <rlog/StdioNode.h>
#include <rlog/rlog.h>

using namespace std;
using namespace boost::filesystem;
using namespace rlog;

bool HasExtension(const string& filename, const string& s) {
  string ext{"." + s};
  if (ext.length() > filename.length()) return false;
  return 0 == filename.compare(filename.length() - ext.length(), ext.length(), ext);
}

struct RiffHeader {
  int8_t id[4];
  uint32_t length;
  int8_t format[4];
};

struct FormatSubchunkHeader {
  int8_t id[4];
  uint32_t subchunk_size;
};

struct FormatSubchunk {
  uint16_t format_tag;
  uint16_t channels;
  uint32_t samples_per_second;
  uint32_t average_bytes_per_second;
  uint16_t block_align;
  uint16_t bits_per_sample;
};

struct FactOrData {
  int8_t tag[4];
};

struct DataChunk {
  uint32_t length;
};

struct FactChunk {
  uint32_t chunkSize;
  uint32_t samplesPerChannel;
};

WavReader::WavReader(const std::string& source, const std::string& dest) : source_(source), dest_(dest) {
  descriptor_ = new WavDescriptor(dest);

  rlog_channel_ = DEF_CHANNEL("info/wav", Log_Debug);
  log.subscribeTo((RLogNode*)RLOG_CHANNEL("info/wav"));
  rLog(rlog_channel_, "reading from %s writing to %s", source.c_str(), dest.c_str());
}

WavReader::~WavReader() {
  delete descriptor_;
  delete rlog_channel_;
}

void WavReader::PublishSnippets() {
  directory_iterator itEnd;
  for (directory_iterator it(source_); it != itEnd; ++it)
    if (!is_directory(it->status()) &&
        //  it->path().filename().string()=="husten.wav" &&
        HasExtension(it->path().filename().string(), "wav"))
      Open(it->path().filename().string(), false);
}

string WavReader::ToString(int8_t* bytes, unsigned int size) { return string{(char*)bytes, size}; }

void WavReader::Open(const std::string& name, bool trace) {
  rLog(rlog_channel_, "opening %s", name.c_str());

  ifstream file{name, ios::in | ios::binary};
  if (!file.is_open()) {
    rLog(rlog_channel_, "unable to read %s", name.c_str());
    return;
  }

  ofstream out{dest_ + "/" + name, ios::out | ios::binary};

  RiffHeader header;
  file.read(reinterpret_cast<char*>(&header), sizeof(RiffHeader));

  if (ToString(header.id, 4) != "RIFF") {
    rLog(rlog_channel_, "ERROR: %s is not a RIFF file", name.c_str());
    return;
  }
  if (ToString(header.format, 4) != "WAVE") {
    rLog(rlog_channel_, "ERROR: %s is not a wav file: %s", name.c_str(), ToString(header.format, 4).c_str());
    return;
  }
  out.write(reinterpret_cast<char*>(&header), sizeof(RiffHeader));

  FormatSubchunkHeader formatSubchunkHeader;
  file.read(reinterpret_cast<char*>(&formatSubchunkHeader), sizeof(FormatSubchunkHeader));

  if (ToString(formatSubchunkHeader.id, 4) != "fmt ") {
    rLog(rlog_channel_, "ERROR: %s expecting 'fmt' for subchunk header; got '%s'", name.c_str(),
         ToString(formatSubchunkHeader.id, 4).c_str());
    return;
  }

  out.write(reinterpret_cast<char*>(&formatSubchunkHeader), sizeof(FormatSubchunkHeader));

  FormatSubchunk formatSubchunk;
  file.read(reinterpret_cast<char*>(&formatSubchunk), sizeof(FormatSubchunk));

  out.write(reinterpret_cast<char*>(&formatSubchunk), sizeof(FormatSubchunk));

  rLog(rlog_channel_, "format tag: %u", formatSubchunk.format_tag);  // show as hex?
  rLog(rlog_channel_, "samples per second: %u", formatSubchunk.samples_per_second);
  rLog(rlog_channel_, "channels: %u", formatSubchunk.channels);
  rLog(rlog_channel_, "bits per sample: %u", formatSubchunk.bits_per_sample);

  auto bytes = formatSubchunkHeader.subchunk_size - sizeof(FormatSubchunk);

  auto additionalBytes = new char[bytes];
  file.read(additionalBytes, bytes);
  out.write(additionalBytes, bytes);

  FactOrData factOrData;
  file.read(reinterpret_cast<char*>(&factOrData), sizeof(FactOrData));
  out.write(reinterpret_cast<char*>(&factOrData), sizeof(FactOrData));

  if (ToString(factOrData.tag, 4) == "fact") {
    FactChunk factChunk;
    file.read(reinterpret_cast<char*>(&factChunk), sizeof(FactChunk));
    out.write(reinterpret_cast<char*>(&factChunk), sizeof(FactChunk));

    file.read(reinterpret_cast<char*>(&factOrData), sizeof(FactOrData));
    out.write(reinterpret_cast<char*>(&factOrData), sizeof(FactOrData));

    rLog(rlog_channel_, "samples per channel: %u", factChunk.samplesPerChannel);
  }

  if (ToString(factOrData.tag, 4) != "data") {
    string tag{ToString(factOrData.tag, 4)};
    rLog(rlog_channel_, "%s ERROR: unknown tag>%s<", name.c_str(), tag.c_str());
    return;
  }

  DataChunk dataChunk;
  file.read(reinterpret_cast<char*>(&dataChunk), sizeof(DataChunk));

  rLog(rlog_channel_, "riff header size = %u", sizeof(RiffHeader));
  rLog(rlog_channel_, "subchunk header size = %u", sizeof(FormatSubchunkHeader));
  rLog(rlog_channel_, "subchunk size = %u", formatSubchunkHeader.subchunk_size);
  rLog(rlog_channel_, "data length = %u", dataChunk.length);

  // TODO if odd there is a padding byte!
  auto data = new char[dataChunk.length];
  file.read(data, dataChunk.length);
  file.close();

  // all of it
  //   out.write(data, dataChunk.length);
  // TODO: multiple channels
  uint32_t secondsDesired{10};
  if (formatSubchunk.bits_per_sample == 0) formatSubchunk.bits_per_sample = 8;
  uint32_t bytes_per_sample{formatSubchunk.bits_per_sample / uint32_t{8}};
  uint32_t samples_to_write{secondsDesired * formatSubchunk.samples_per_second};
  uint32_t total_samples{dataChunk.length / bytes_per_sample};

  samples_to_write = min(samples_to_write, total_samples);

  uint32_t totalSeconds{total_samples / formatSubchunk.samples_per_second};
  rLog(rlog_channel_, "total seconds %u ", totalSeconds);

  dataChunk.length = DataLength(bytes_per_sample, samples_to_write, formatSubchunk.channels);
  out.write(reinterpret_cast<char*>(&dataChunk), sizeof(DataChunk));

  uint32_t starting_sample{totalSeconds >= 10 ? 10 * formatSubchunk.samples_per_second : 0};
  WriteSamples(&out, data, starting_sample, samples_to_write, bytes_per_sample);

  rLog(rlog_channel_, "completed writing %s", name.c_str());
  descriptor_->add(dest_, name, totalSeconds, formatSubchunk.samples_per_second, formatSubchunk.channels);
  out.close();
}

void WavReader::WriteSamples(std::ostream* out, char* data, const uint32_t starting_sample,
                             const uint32_t samples_to_write, const uint32_t bytes_per_sample, const u_int32_t channels) {
  rLog(rlog_channel_, "writing %u samples", samples_to_write);

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

void WavReader::SeekToEndOfHeader(ifstream& file, int subchunk_size) {
  auto bytes = subchunk_size - sizeof(FormatSubchunk) + 1;
  file.seekg(bytes, ios_base::cur);
}

uint32_t WavReader::DataLength(const uint32_t bytes_per_sample, const uint32_t samples, const uint32_t channels) const {
  return bytes_per_sample * samples * channels;
}
