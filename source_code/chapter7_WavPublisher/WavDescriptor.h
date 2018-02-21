/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#ifndef WavDescriptor_h
#define WavDescriptor_h

#include <cstdint>
#include <cstring>
#include <fstream>
#include <string>

struct WavDescriptorRecord {
  int8_t filename[64];
  uint32_t seconds;
  uint32_t samples_per_second;
  uint32_t channels;
};

class WavDescriptor {
 public:
  WavDescriptor(const std::string& dir) {
    outstr = new std::ofstream(dir + "/WavSnippets.dat", std::ios::out | std::ios::binary);
  }

  void add(const std::string& dir, const std::string& filename, uint32_t totalSeconds, uint32_t samples_per_second,
           uint32_t channels) {
    WavDescriptorRecord rec;
    cpy(rec.filename, filename.c_str());
    rec.seconds = totalSeconds;
    rec.samples_per_second = samples_per_second;
    rec.channels = channels;

    outstr->write(reinterpret_cast<char*>(&rec), sizeof(WavDescriptorRecord));
  }

  void cpy(int8_t* dest, const char* src) {
    for (int i = 0; src[i] != 0; i++) dest[i] = src[i];
  }

  ~WavDescriptor() {
    outstr->close();
    delete outstr;
  }

 private:
  std::ofstream* outstr;
};

#endif
