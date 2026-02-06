#include <iostream>
#include <vector>
#include "/fuzz/install/include/soramimi_guitar/webclient.h"
#include "/fuzz/install/include/soramimi_guitar/urlencode.h"
#include "/fuzz/install/include/soramimi_guitar/inetresolver.h"

int main() {
    // Test URL parsing without any network access
    WebClient::URL u("https://example.com:8443/some/path?x=1");
    std::cout << "scheme=" << u.scheme() << "\n";
    std::cout << "host=" << u.host() << "\n";
    std::cout << "port=" << u.port() << "\n";
    std::cout << "path=" << u.path() << "\n";
    std::cout << "isssl=" << (u.isssl() ? "true" : "false") << "\n";

    // Build a small form body
    const char body[] = "hello world";
    WebClient::Post post;
    WebClient::make_multipart_form_data(body, sizeof(body)-1, &post, "----BOUNDARY");
    std::cout << "post_size=" << post.data.size() << " content_type=" << post.content_type << "\n";

    // Use urlencode utility
    std::string enc = url_encode("a b+c/d?=");
    std::cout << "urlenc=" << enc << "\n";

    // Instantiate context and client (no networking)
    WebContext cx(WebClient::HTTP_1_1);
    WebClient wc(&cx);
    wc.set_http_version(WebClient::HTTP_1_1);

    // Try InetResolver interface without actual resolve
    InetResolver::Addr addr; // not filled; just exercise API
    std::cout << "addr_empty=" << (addr.empty() ? "true" : "false") << "\n";

    std::cout << "OK" << std::endl;
    return 0;
}
