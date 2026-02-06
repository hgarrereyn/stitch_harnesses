#include <iostream>
#include <string>
#include <string_view>
#include "uWebSockets/Utilities.h"
#include "uWebSockets/QueryParser.h"
#include "uWebSockets/ChunkedEncoding.h"

int main() {
    // Test Utilities: u64toa
    char buf[32] = {0};
    uint64_t val = 1234567890123456789ULL;
    int n = uWS::utils::u64toa(val, buf);
    std::cout << "u64toa: length=" << n << ", value=" << std::string(buf, n) << "\n";

    // Test QueryParser: decode a simple query
    std::string query = "?name=John+Doe&msg=Hello%20World";
    std::string_view name = uWS::getDecodedQueryValue("name", query);
    std::string_view msg = uWS::getDecodedQueryValue("msg", query);
    std::cout << "name=" << name << ", msg=" << msg << "\n";

    // Test ChunkedEncoding: iterate chunks
    std::string chunked = "4\r\nWiki\r\n5\r\npedia\r\n0\r\n\r\n";
    std::string_view data(chunked);
    uint64_t state = 0;
    for (auto it : uWS::ChunkIterator(&data, &state)) {
        std::cout << it << "|";
    }
    std::cout << "\n";

    return 0;
}
