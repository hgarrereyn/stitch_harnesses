#include <cpr/cpr.h>
#include <iostream>

int main() {
    std::string original = "hello world? a+b&c=d";
    auto enc = cpr::util::urlEncode(original);
    auto dec = cpr::util::urlDecode(std::string_view(enc.data(), enc.size()));
    std::cout << enc << "\n";
    std::cout << dec << "\n";

    cpr::Session s; // basic object from the API
    s.SetUrl(cpr::Url{"http://example.com"}); // do not perform a request
    return 0;
}
