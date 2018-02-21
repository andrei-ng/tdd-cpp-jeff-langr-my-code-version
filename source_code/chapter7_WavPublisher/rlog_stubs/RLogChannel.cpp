#include <rlog/RLogChannel.h>

#include <map>

#include <rlog/RLogNode.h>
#include <rlog/rlog.h>

namespace rlog {

RLogChannel::RLogChannel(const std::string &name, LogLevel level) {}
RLogChannel::~RLogChannel() {}

void RLogChannel::publish(const RLogData &data) {}

std::string name_return("");
const std::string &RLogChannel::name() const { return name_return; }

LogLevel RLogChannel::logLevel() const { return LogLevel(); }
void RLogChannel::setLogLevel(LogLevel /*level*/) {}

RLogChannel *GetComponentChannel(const char *component, const char *path, LogLevel level) { return nullptr; }
RLogChannel *RLogChannel::getComponent(RLogChannel *componentParent, const char *component) { return nullptr; }
}
