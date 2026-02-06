#include <iostream>
#include <string>
#include "cpp/htmlparser/url.h"

int main() {
    std::string u = "https://user:pass@example.com:443/path?x=1#frag";
    htmlparser::URL url(u);
    std::cout << (url.is_valid() ? "valid" : "invalid") << "\n";
    std::cout << url.protocol() << "\n";
    std::cout << url.hostname() << "\n";
    std::cout << url.port() << "\n";
    std::cout << std::string(url.path_params_fragment()) << "\n";
    return 0;
}
