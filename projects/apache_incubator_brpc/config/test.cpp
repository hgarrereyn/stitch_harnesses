#include <iostream>
#include <brpc/uri.h>
#include <brpc/channel.h>
#include <brpc/controller.h>

int main() {
    // Test URI parsing
    brpc::URI uri;
    if (uri.SetHttpURL("http://example.com:80/hello/world?x=1#frag") != 0) {
        std::cerr << "Failed to parse URI" << std::endl;
        return 1;
    }
    std::cout << "Scheme: " << uri.scheme() << " Host: " << uri.host() << " Path: " << uri.path() << std::endl;

    // Test constructing a Channel (no request will be sent)
    brpc::ChannelOptions options;
    options.protocol = "http";
    options.timeout_ms = 100; // no effect since we won't send
    brpc::Channel channel;
    if (channel.Init("127.0.0.1:65535", &options) != 0) {
        std::cerr << "Channel init failed" << std::endl;
        return 1;
    }

    // Controller basic usage
    brpc::Controller cntl;
    cntl.Reset();
    std::cout << "bRPC basic setup OK" << std::endl;
    return 0;
}
