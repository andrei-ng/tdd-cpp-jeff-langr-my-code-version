/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#ifndef WavReader_h
#define WavReader_h

#include <boost/filesystem.hpp>
#include <fstream>
#include <string>

#include "WavDescriptor.h"
#include "rlog/RLogChannel.h"
#include "rlog/StdioNode.h"

bool HasExtension(const std::string& text, const std::string& substring);

class WavReader {
 public:
  WavReader(const std::string& source, const std::string& dest);
  virtual ~WavReader();
  void Open(const std::string& name, bool trace);
  void List(const boost::filesystem::path& dir, const std::string& filename,
            std::vector<boost::filesystem::path>& found) const;
  void ListAll() const;
  void PublishSnippets();

 private:
  rlog::StdioNode log{STDERR_FILENO};
  WavDescriptor* descriptor_;

  void SeekToEndOfHeader(std::ifstream& file, int headerLength);
  std::string ToString(int8_t* c, unsigned int size);

  rlog::RLogChannel* channel;

  std::string source_;
  std::string dest_;
};

#endif
