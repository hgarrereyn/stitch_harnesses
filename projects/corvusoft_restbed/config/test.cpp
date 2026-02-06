#include <iostream>
#include <restbed>

using namespace restbed;

int main() {
    std::string text = "Hello, Restbed";
    auto upper = String::uppercase(text);

    auto uri = Uri::parse("http://example.com:8080/path?x=1#frag");
    std::cout << upper << "\n";
    std::cout << uri.get_scheme() << "://" << uri.get_authority() << uri.get_path() << "?" << uri.get_query() << "#" << uri.get_fragment() << "\n";

    auto resource = std::make_shared<Resource>();
    resource->set_path("/test");

    auto settings = std::make_shared<Settings>();
    settings->set_port(0);

    Service service; // Do not start; just ensure types are usable

    std::cout << "OK\n";
    return 0;
}
