#include <rlog/StdioNode.h>

namespace rlog {

StdioNode global_node;

StdioNode::StdioNode(int fdOut, int flags) {}
StdioNode::StdioNode(int fdOut, bool colorize_if_tty) {}
StdioNode::~StdioNode() {}

void StdioNode::subscribeTo(RLogNode *node) {}
void StdioNode::publish(const RLogData &data) {}

StdioNode &StdioNode::operator=(const StdioNode & /*input_node*/) {return global_node;}
};
