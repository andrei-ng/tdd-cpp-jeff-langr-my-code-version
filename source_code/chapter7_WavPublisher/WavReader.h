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
#include <memory>
#include <string>

#include "rlog/RLogChannel.h"
#include "rlog/StdioNode.h"

#include "FileUtil.h"
#include "WavDescriptor.h"
#include "WavStructs.h"

namespace wav_reader {

bool HasExtension(const std::string& text, const std::string& substring);
struct FormatSubchunkHeader;

class WavReader {
 public:
  WavReader(const std::string& source, const std::string& dest, std::shared_ptr<WavDescriptor> descriptor = nullptr);
  virtual ~WavReader();
  void Open(const std::string& name, bool trace);
  void List(const boost::filesystem::path& dir, const std::string& filename,
            std::vector<boost::filesystem::path>& found) const;
  void ListAll() const;
  void PublishSnippets();

  void SelectFileUtility(std::shared_ptr<FileUtil> file_util);

  uint32_t total_seconds_to_write;

 private:
  void SeekToEndOfHeader(std::ifstream& file, int headerLength);
  void FileReadChunk(std::ifstream& file, DataChunk& data_chunk);

  void ReadAndWriteHeaders(const std::string& name, std::ifstream& file, std::ostream& out,
                           FormatSubchunk& format_subchunk, FormatSubchunkHeader& format_subchunk_header);

  char* FileReadData(std::ifstream& file, const uint32_t length);

  std::string ToString(int8_t* c, unsigned int size);

  rlog::StdioNode log{STDERR_FILENO};
  rlog::RLogChannel* rlog_channel_;
  std::string source_;
  std::string dest_;
  std::shared_ptr<WavDescriptor> descriptor_;
  std::shared_ptr<FileUtil> file_util_;
};
}

#endif
