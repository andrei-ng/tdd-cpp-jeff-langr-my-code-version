#include "StreamUtil.h"

namespace stream_util {
std::streamsize Size(std::istream& stream) {
  stream.seekg(0, std::ios::end);
  return stream.tellg();
}
}
